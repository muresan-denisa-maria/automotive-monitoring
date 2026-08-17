#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include "TelemetryData.h"

struct TransmissionConfiguration
{
    double wheelRadius;

    double finalDriveRatio;

    double firstGearRatio;
    double secondGearRatio;
    double thirdGearRatio;
    double fourthGearRatio;
    double fifthGearRatio;

    double transmissionEfficiency;
};

class Transmission
{
public:
    Transmission(
        const TransmissionConfiguration& configuration,
        const TransmissionData& initialData
    );

    void update(
        double deltaTime,
        double engineRpm,
        double clutchTorque
    );

    TransmissionData getTelemetry() const;

private:
    TransmissionConfiguration configuration;
    TransmissionData data;
};

#endif