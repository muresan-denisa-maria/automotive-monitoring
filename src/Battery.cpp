#include "Battery.h"

Battery::Battery(const BatteryData& initialData)
{
    data = initialData;
}

void Battery::update(double deltaTime)
{
    // Vom implementa aici simularea bateriei
}

BatteryData Battery::getTelemetry() const
{
    return data;
}