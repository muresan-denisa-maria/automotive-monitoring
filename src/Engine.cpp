#include "Engine.h"


Engine::Engine(
    const EngineConfiguration& configuration,
    const EngineData& initialData
)
{
    this->configuration =
        configuration;

    this->data =
        initialData;

    coolingSystemHealth =
        1.0;
}


void Engine::setCoolingSystemHealth(
    double health
)
{
    if (health < 0.0)
    {
        health = 0.0;
    }

    if (health > 1.0)
    {
        health = 1.0;
    }

    coolingSystemHealth =
        health;
}


void Engine::update(
    double deltaTime,
    double throttlePosition,
    double loadTorque,
    bool startCommand,
    double ambientTemperature
)
{
    if (throttlePosition < 0.0)
    {
        throttlePosition = 0.0;
    }

    if (throttlePosition > 100.0)
    {
        throttlePosition = 100.0;
    }

    double throttle =
        throttlePosition / 100.0;

    double rpmRatio = 0.0;

    if (configuration.maxRpm > 0.0)
    {
        rpmRatio =
            data.rpm /
            configuration.maxRpm;
    }

    if (rpmRatio < 0.0)
    {
        rpmRatio = 0.0;
    }

    if (rpmRatio > 1.0)
    {
        rpmRatio = 1.0;
    }

    bool engineRunning =
        data.rpm >=
        configuration.minimumCombustionRpm;

    double combustionTorque =
        0.0;

    if (engineRunning)
    {
        combustionTorque =
            configuration.maximumTorque *
            throttle;

        if (data.rpm <
            configuration.idleRpm)
        {
            double rpmDifference =
                configuration.idleRpm -
                data.rpm;

            double idleTorque =
                configuration.frictionTorque +
                rpmDifference * 0.05;

            combustionTorque +=
                idleTorque;
        }
    }

    double availableTorque =
        combustionTorque -
        configuration.frictionTorque;

    double starterTorque =
        0.0;

    if (startCommand &&
        data.rpm <
            configuration.idleRpm)
    {
        starterTorque =
            configuration.starterTorque;
    }

    double netTorque =
        availableTorque +
        starterTorque -
        loadTorque;

    double angularAcceleration =
        netTorque /
        configuration.engineInertia;

    double angularVelocity =
        data.rpm *
        2.0 *
        3.14159265359 /
        60.0;

    angularVelocity +=
        angularAcceleration *
        deltaTime;

    if (angularVelocity < 0.0)
    {
        angularVelocity = 0.0;
    }

    data.rpm =
        angularVelocity *
        60.0 /
        (
            2.0 *
            3.14159265359
        );

    if (data.rpm >
        configuration.maxRpm)
    {
        data.rpm =
            configuration.maxRpm;
    }

    if (!startCommand &&
        throttlePosition == 0.0 &&
        data.rpm >
            configuration.minimumCombustionRpm &&
        data.rpm <
            configuration.idleRpm)
    {
        data.rpm =
            configuration.idleRpm;
    }

    rpmRatio = 0.0;

    if (configuration.maxRpm > 0.0)
    {
        rpmRatio =
            data.rpm /
            configuration.maxRpm;
    }

    if (rpmRatio < 0.0)
    {
        rpmRatio = 0.0;
    }

    if (rpmRatio > 1.0)
    {
        rpmRatio = 1.0;
    }

    engineRunning =
        data.rpm >=
        configuration.minimumCombustionRpm;

    data.engineTorque =
        availableTorque;

    if (data.engineTorque < 0.0)
    {
        data.engineTorque = 0.0;
    }

    data.throttlePosition =
        throttlePosition;


    double engineHeatPower =
        0.0;

    if (engineRunning)
    {
        double engineLoadFactor =
            0.65 * throttle +
            0.35 * rpmRatio;

        engineHeatPower =
            configuration.idleHeatPower +
            (
                configuration.maximumHeatPower -
                configuration.idleHeatPower
            ) *
            engineLoadFactor;
    }

    double engineToCoolantPower =
        configuration.engineToCoolantCoefficient *
        (
            data.engineTemperature -
            data.coolantTemperature
        );

    double engineToOilPower =
        configuration.engineToOilCoefficient *
        (
            data.engineTemperature -
            data.oilTemperature
        );

    double engineNetHeatPower =
        engineHeatPower -
        engineToCoolantPower -
        engineToOilPower;

    if (configuration.engineThermalCapacity > 0.0)
    {
        data.engineTemperature +=
            (
                engineNetHeatPower *
                deltaTime
            ) /
            configuration.engineThermalCapacity;
    }


    double oilCoolingPower =
        configuration.oilCoolingCoefficient *
        (
            data.oilTemperature -
            ambientTemperature
        );

    double oilNetHeatPower =
        engineToOilPower -
        oilCoolingPower;

    if (configuration.oilThermalCapacity > 0.0)
    {
        data.oilTemperature +=
            (
                oilNetHeatPower *
                deltaTime
            ) /
            configuration.oilThermalCapacity;
    }


    if (engineRunning)
    {
        data.coolantPumpSpeed =
            data.rpm *
            configuration.coolantPumpRatio;
    }
    else
    {
        data.coolantPumpSpeed =
            0.0;
    }

    double maximumPumpSpeed =
        configuration.maxRpm *
        configuration.coolantPumpRatio;

    double coolantFlowRatio =
        0.0;

    if (maximumPumpSpeed > 0.0)
    {
        coolantFlowRatio =
            data.coolantPumpSpeed /
            maximumPumpSpeed;
    }

    if (coolantFlowRatio < 0.0)
    {
        coolantFlowRatio = 0.0;
    }

    if (coolantFlowRatio > 1.0)
    {
        coolantFlowRatio = 1.0;
    }

    double effectiveCoolantFlowRatio =
        coolantFlowRatio *
        coolingSystemHealth;

    data.coolantFlowRate =
        configuration.maximumCoolantFlowRate *
        effectiveCoolantFlowRatio;

    double radiatorCoolingPower =
        configuration.radiatorCoolingCoefficient *
        effectiveCoolantFlowRatio *
        (
            data.coolantTemperature -
            ambientTemperature
        );

    double coolantNetHeatPower =
        engineToCoolantPower -
        radiatorCoolingPower;

    if (configuration.coolantThermalCapacity > 0.0)
    {
        data.coolantTemperature +=
            (
                coolantNetHeatPower *
                deltaTime
            ) /
            configuration.coolantThermalCapacity;
    }


    if (engineRunning)
    {
        data.coolantPressure =
            configuration.minimumCoolantPressure +
            (
                configuration.maximumCoolantPressure -
                configuration.minimumCoolantPressure
            ) *
            effectiveCoolantFlowRatio;
    }
    else
    {
        data.coolantPressure =
            0.0;
    }


    if (engineRunning)
    {
        data.oilPressure =
            configuration.minimumOilPressure +
            (
                configuration.maximumOilPressure -
                configuration.minimumOilPressure
            ) *
            rpmRatio;
    }
    else
    {
        data.oilPressure =
            0.0;
    }


    double intakeTargetTemperature =
        ambientTemperature;

    if (engineRunning)
    {
        intakeTargetTemperature +=
            (
                data.engineTemperature -
                ambientTemperature
            ) *
            configuration.intakeHeatTransferFactor *
            (
                1.0 -
                0.5 * throttle
            );
    }

    if (configuration.intakeResponseTime > 0.0)
    {
        data.intakeAirTemperature +=
            (
                intakeTargetTemperature -
                data.intakeAirTemperature
            ) *
            deltaTime /
            configuration.intakeResponseTime;
    }


    if (engineRunning)
    {
        data.intakeManifoldPressure =
            configuration.minimumManifoldPressure +
            (
                configuration.ambientPressure -
                configuration.minimumManifoldPressure
            ) *
            throttle;
    }
    else
    {
        data.intakeManifoldPressure =
            configuration.ambientPressure;
    }


    double exhaustTargetTemperature =
        ambientTemperature;

    if (engineRunning)
    {
        double exhaustLoadFactor =
            0.7 * throttle +
            0.3 * rpmRatio;

        exhaustTargetTemperature =
            configuration.idleExhaustGasTemperature +
            (
                configuration.maximumExhaustGasTemperature -
                configuration.idleExhaustGasTemperature
            ) *
            exhaustLoadFactor;
    }

    if (configuration.exhaustResponseTime > 0.0)
    {
        data.exhaustGasTemperature +=
            (
                exhaustTargetTemperature -
                data.exhaustGasTemperature
            ) *
            deltaTime /
            configuration.exhaustResponseTime;
    }


    if (engineRunning)
    {
        data.exhaustBackpressure =
            configuration.maximumExhaustBackpressure *
            rpmRatio *
            rpmRatio *
            (
                0.3 +
                0.7 * throttle
            );
    }
    else
    {
        data.exhaustBackpressure =
            0.0;
    }


    if (engineRunning)
    {
        data.exhaustOxygenPercentage =
            configuration.maximumExhaustOxygenPercentage -
            (
                configuration.maximumExhaustOxygenPercentage -
                configuration.minimumExhaustOxygenPercentage
            ) *
            throttle;

        if (data.exhaustOxygenPercentage <
            configuration.minimumExhaustOxygenPercentage)
        {
            data.exhaustOxygenPercentage =
                configuration.minimumExhaustOxygenPercentage;
        }
    }
    else
    {
        data.exhaustOxygenPercentage =
            21.0;
    }


    if (data.engineTemperature <
        ambientTemperature)
    {
        data.engineTemperature =
            ambientTemperature;
    }

    if (data.oilTemperature <
        ambientTemperature)
    {
        data.oilTemperature =
            ambientTemperature;
    }

    if (data.coolantTemperature <
        ambientTemperature)
    {
        data.coolantTemperature =
            ambientTemperature;
    }
}


EngineData Engine::getTelemetry() const
{
    return data;
}