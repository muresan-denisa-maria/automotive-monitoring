#ifndef BATTERY_H
#define BATTERY_H

#include "TelemetryData.h"

class Battery
{
public:
    Battery(const BatteryData& initialData);

    void update(double deltaTime);

    BatteryData getTelemetry() const;

private:
    BatteryData data;
};

#endif