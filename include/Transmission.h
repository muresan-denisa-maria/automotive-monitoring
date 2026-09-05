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

    double thermalCapacity;
    double coolingCoefficient;
    double ambientTemperature;
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
        double clutchTorque,
        int gearPosition,
        double vehicleMass,
        double brakeForce
    );

    void setHealth(
        double health
    );

    TransmissionData getTelemetry() const;

private:
    TransmissionConfiguration configuration;
    TransmissionData data;

    double health;
};

#endif