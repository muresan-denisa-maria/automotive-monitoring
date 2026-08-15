#ifndef ALTERNATOR_H
#define ALTERNATOR_H

#include "TelemetryData.h"
struct AlternatorConfiguration
{
    double maximumCurrent; //curentul maxim produs de alternator
    double maximumRpm; //turatia la care alternatorul produce curentul maxim
    double nominalVoltage; //tensiunea nominala a alternatorului
    double efficiency; //eficienta alternatorului
    double thermalCapacity; //capacitatea termica a alternatorului
    double coolingCoefficient; //coeficientul de racire al alternatorului
    double ambientTemperature; //temperatura mediului
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

    AlternatorData getTelemetry() const;

private:
    AlternatorConfiguration configuration;
    AlternatorData data;
};

#endif