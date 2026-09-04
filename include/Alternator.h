#ifndef ALTERNATOR_H
#define ALTERNATOR_H

#include "TelemetryData.h"

struct AlternatorConfiguration
{
    double maximumCurrent;
    double maximumRpm;
    double nominalVoltage;

    double efficiency;

    double thermalCapacity;
    double coolingCoefficient;
    double ambientTemperature;
};

class Alternator
{
public:
    Alternator(
        const AlternatorConfiguration& configuration,
        const AlternatorData& initialData
    );

    void update(
        double deltaTime,
        double engineRpm
    );

    void setHealth(
        double health
    );

    AlternatorData getTelemetry() const;

private:
    AlternatorConfiguration configuration;
    AlternatorData data;

    double health;
};

#endif