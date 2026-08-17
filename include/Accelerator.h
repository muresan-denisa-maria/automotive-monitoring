#ifndef ACCELERATOR_H
#define ACCELERATOR_H

#include "TelemetryData.h"

struct AcceleratorConfiguration
{
    double maximumThrottle;

    double throttleResponseTime;
};

class Accelerator
{
public:
    Accelerator(
        const AcceleratorConfiguration& configuration,
        const AcceleratorData& initialData
    );

    void update(
        double deltaTime,
        double acceleratorInput
    );

    AcceleratorData getTelemetry() const;

private:
    AcceleratorConfiguration configuration;
    AcceleratorData data;
};

#endif