#ifndef STARTER_H
#define STARTER_H

#include "TelemetryData.h"

struct StarterConfiguration
{
    double maximumCurrent; //curentul maxim consumat de starter
    double minimumVoltage; //tensiunea minima necesara pentru starter
    double efficiency; //eficienta starterului
};

class Starter
{
public:
    Starter(
        const StarterConfiguration& configuration,
        const StarterData& initialData
    );

    void update(
        double deltaTime,
        double batteryVoltage,
        bool startCommand
    );

    StarterData getTelemetry() const;

private:
    StarterConfiguration configuration;
    StarterData data;
};

#endif