#include "Transmission.h"

Transmission::Transmission(const TransmissionData& initialData)
{
    data = initialData;
}

void Transmission::update(double deltaTime)
{
    // Vom implementa aici simularea transmisiei.
}

TransmissionData Transmission::getTelemetry() const
{
    return data;
}