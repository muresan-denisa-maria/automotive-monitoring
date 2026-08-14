#include "Brake.h"

Brake::Brake(const BrakeData& initialData)
{
    data = initialData;
}

void Brake::update(double deltaTime)
{
    // Vom implementa aici simularea franelor.
}

BrakeData Brake::getTelemetry() const
{
    return data;
}