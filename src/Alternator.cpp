#include "Alternator.h"


Alternator::Alternator(
    const AlternatorConfiguration& configuration,
    const AlternatorData& initialData
)
{
    this->configuration =
        configuration;

    this->data =
        initialData;

    health =
        1.0;
}


void Alternator::setHealth(
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


void Alternator::update(
    double deltaTime,
    double engineRpm
)
{
    double rpmRatio =
        0.0;

    if (configuration.maximumRpm > 0.0)
    {
        rpmRatio =
            engineRpm /
            configuration.maximumRpm;
    }

    if (rpmRatio < 0.0)
    {
        rpmRatio =
            0.0;
    }

    if (rpmRatio > 1.0)
    {
        rpmRatio =
            1.0;
    }

    double effectiveMaximumCurrent =
        configuration.maximumCurrent *
        health;

    data.alternatorCurrent =
        rpmRatio *
        effectiveMaximumCurrent;

    if (engineRpm > 0.0)
    {
        data.alternatorVoltage =
            configuration.nominalVoltage;
    }
    else
    {
        data.alternatorVoltage =
            0.0;

        data.alternatorCurrent =
            0.0;
    }

    double electricalPower =
        data.alternatorVoltage *
        data.alternatorCurrent;

    double efficiency =
        configuration.efficiency;

    if (efficiency < 0.01)
    {
        efficiency =
            0.01;
    }

    if (efficiency > 1.0)
    {
        efficiency =
            1.0;
    }

    double mechanicalPower =
        electricalPower /
        efficiency;

    double powerLoss =
        mechanicalPower -
        electricalPower;

    double coolingPower =
        configuration.coolingCoefficient *
        (
            data.alternatorTemperature -
            configuration.ambientTemperature
        );

    double netHeatPower =
        powerLoss -
        coolingPower;

    if (configuration.thermalCapacity > 0.0)
    {
        data.alternatorTemperature +=
            (
                netHeatPower *
                deltaTime
            ) /
            configuration.thermalCapacity;
    }

    if (data.alternatorTemperature <
        configuration.ambientTemperature)
    {
        data.alternatorTemperature =
            configuration.ambientTemperature;
    }
}


AlternatorData Alternator::getTelemetry() const
{
    return data;
}