#ifndef BRAKE_H
#define BRAKE_H

#include "TelemetryData.h"

struct BrakeConfiguration
{
    double maximumBrakeForce;

    double brakeDiscMass;
    double brakeDiscSpecificHeat;
    double brakeDiscArea;

    double brakeEnergyFraction;

    double coolingCoefficient;

    double brakePadWearCoefficient;

    double maximumBrakePressure;
};

class Brake
{
public:
    Brake(
        const BrakeConfiguration& configuration,
        const BrakeData& initialData
    );

    void update(
        double deltaTime,
        double vehicleMass,
        double vehicleSpeed,
        double brakeInput,
        double ambientTemperature
    );

    BrakeData getTelemetry() const;

private:
    BrakeConfiguration configuration;
    BrakeData data;
};

#endif