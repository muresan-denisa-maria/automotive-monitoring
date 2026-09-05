#ifndef BATTERY_H
#define BATTERY_H

#include "TelemetryData.h"

struct BatteryConfiguration
{
    double nominalVoltage;
    double capacityAh;
    double internalResistance;
    double maximumCurrent;

    double thermalCapacity;
    double coolingCoefficient;
};

class Battery
{
public:
    Battery(
        const BatteryConfiguration& configuration,
        const BatteryData& initialData
    );

    void update(
        double deltaTime,
        double alternatorCurrent,
        double starterCurrent,
        double electricalLoad,
        double ambientTemperature
    );

    void setHealth(
        double health
    );

    BatteryData getTelemetry() const;

private:
    BatteryConfiguration configuration;
    BatteryData data;

    double health;
};

#endif