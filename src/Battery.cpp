#include "Battery.h"


Battery::Battery(
    const BatteryConfiguration& configuration,
    const BatteryData& initialData
)
{
    this->configuration =
        configuration;

    this->data =
        initialData;

    health =
        1.0;
}


void Battery::setHealth(
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


void Battery::update(
    double deltaTime,
    double alternatorCurrent,
    double starterCurrent,
    double electricalLoad,
    double ambientTemperature
)
{
    double batteryCurrent =
        electricalLoad +
        starterCurrent -
        alternatorCurrent;

    double effectiveMaximumCurrent =
        configuration.maximumCurrent *
        (
            0.5 +
            0.5 * health
        );

    if (batteryCurrent >
        effectiveMaximumCurrent)
    {
        batteryCurrent =
            effectiveMaximumCurrent;
    }

    if (batteryCurrent <
        -effectiveMaximumCurrent)
    {
        batteryCurrent =
            -effectiveMaximumCurrent;
    }

    data.batteryCurrent =
        batteryCurrent;


    double stateOfChargeFraction =
        data.batteryStateOfCharge /
        100.0;

    double openCircuitVoltage =
        configuration.nominalVoltage *
        (
            0.9 +
            0.1 *
            stateOfChargeFraction
        );


    double effectiveInternalResistance =
        configuration.internalResistance *
        (
            1.0 +
            4.0 *
            (
                1.0 -
                health
            )
        );


    data.batteryVoltage =
        openCircuitVoltage -
        batteryCurrent *
        effectiveInternalResistance;

    if (data.batteryVoltage < 0.0)
    {
        data.batteryVoltage = 0.0;
    }


    double effectiveCapacity =
        configuration.capacityAh *
        (
            0.4 +
            0.6 * health
        );

    if (effectiveCapacity > 0.0)
    {
        double chargeChangeAh =
            batteryCurrent *
            deltaTime /
            3600.0;

        data.batteryStateOfCharge -=
            (
                chargeChangeAh /
                effectiveCapacity
            ) *
            100.0;
    }

    if (data.batteryStateOfCharge < 0.0)
    {
        data.batteryStateOfCharge = 0.0;
    }

    if (data.batteryStateOfCharge > 100.0)
    {
        data.batteryStateOfCharge = 100.0;
    }


    double heatPower =
        batteryCurrent *
        batteryCurrent *
        effectiveInternalResistance;

    double coolingPower =
        configuration.coolingCoefficient *
        (
            data.batteryTemperature -
            ambientTemperature
        );

    double netHeatPower =
        heatPower -
        coolingPower;

    if (configuration.thermalCapacity > 0.0)
    {
        data.batteryTemperature +=
            (
                netHeatPower *
                deltaTime
            ) /
            configuration.thermalCapacity;
    }

    if (data.batteryTemperature <
        ambientTemperature)
    {
        data.batteryTemperature =
            ambientTemperature;
    }
}


BatteryData Battery::getTelemetry() const
{
    return data;
}