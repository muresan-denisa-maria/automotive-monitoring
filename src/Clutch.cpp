#include "Clutch.h"


Clutch::Clutch(
    const ClutchConfiguration& configuration,
    const ClutchData& initialData
)
{
    this->configuration =
        configuration;

    data =
        initialData;

    health =
        1.0;
}


void Clutch::setHealth(
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

    this->health =
        health;
}


void Clutch::update(
    double deltaTime,
    double engineTorque,
    double engineRpm,
    double transmissionRpm,
    double clutchInput,
    double ambientTemperature
)
{
    if (clutchInput < 0.0)
    {
        clutchInput = 0.0;
    }

    if (clutchInput > 100.0)
    {
        clutchInput = 100.0;
    }


    double clutchEngagement =
        1.0 -
        clutchInput /
        100.0;


    data.clutchEngagement =
        clutchEngagement *
        100.0;


    double maximumTransmittedTorque =
        configuration.maximumClutchTorque *
        clutchEngagement *
        health;


    double engineAngularVelocity =
        engineRpm *
        2.0 *
        3.14159265359 /
        60.0;


    double transmissionAngularVelocity =
        transmissionRpm *
        2.0 *
        3.14159265359 /
        60.0;


    double slipAngularVelocity =
        engineAngularVelocity -
        transmissionAngularVelocity;


    double effectiveSlipTorqueCoefficient =
        configuration.slipTorqueCoefficient *
        health;


    double synchronizationTorque =
        effectiveSlipTorqueCoefficient *
        slipAngularVelocity *
        clutchEngagement;


    double transmittedTorque =
        engineTorque *
        clutchEngagement +
        synchronizationTorque;


    if (transmittedTorque >
        maximumTransmittedTorque)
    {
        transmittedTorque =
            maximumTransmittedTorque;
    }


    if (transmittedTorque <
        -maximumTransmittedTorque)
    {
        transmittedTorque =
            -maximumTransmittedTorque;
    }


    data.transmittedTorque =
        transmittedTorque;


    data.clutchSlip =
        engineRpm -
        transmissionRpm;


    double slipPower =
        transmittedTorque *
        slipAngularVelocity;


    if (slipPower < 0.0)
    {
        slipPower =
            -slipPower;
    }


    double slipEnergy =
        slipPower *
        deltaTime;


    double clutchEnergy =
        slipEnergy *
        configuration.clutchEnergyFraction;


    double thermalCapacity =
        configuration.clutchDiscMass *
        configuration.clutchDiscSpecificHeat;


    if (thermalCapacity > 0.0)
    {
        data.clutchDiscTemperature +=
            clutchEnergy /
            thermalCapacity;
    }


    double coolingPower =
        configuration.coolingCoefficient *
        (
            data.clutchDiscTemperature -
            ambientTemperature
        );


    double coolingEnergy =
        coolingPower *
        deltaTime;


    if (thermalCapacity > 0.0)
    {
        data.clutchDiscTemperature -=
            coolingEnergy /
            thermalCapacity;
    }


    if (data.clutchDiscTemperature <
        ambientTemperature)
    {
        data.clutchDiscTemperature =
            ambientTemperature;
    }
}


ClutchData Clutch::getTelemetry() const
{
    return data;
}