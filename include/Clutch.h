#ifndef CLUTCH_H
#define CLUTCH_H

#include "TelemetryData.h"

struct ClutchConfiguration
{
    double maximumClutchTorque;

    double clutchDiscMass;
    double clutchDiscSpecificHeat;

    double clutchEnergyFraction;

    double coolingCoefficient;

    double slipTorqueCoefficient;
};

class Clutch
{
public:
    Clutch(
        const ClutchConfiguration& configuration,
        const ClutchData& initialData
    );

    void update(
        double deltaTime,
        double engineTorque,
        double engineRpm,
        double transmissionRpm,
        double clutchInput,
        double ambientTemperature
    );

    ClutchData getTelemetry() const;

private:
    ClutchConfiguration configuration;
    ClutchData data;
};

#endif