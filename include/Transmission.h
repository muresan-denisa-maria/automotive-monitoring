#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include "TelemetryData.h"

class Transmission
{
public:
    Transmission(const TransmissionData& initialData);

    void update(double deltaTime);

    TransmissionData getTelemetry() const;

private:
    TransmissionData data;
};

#endif