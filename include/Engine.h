#ifndef ENGINE_H
#define ENGINE_H

#include "TelemetryData.h"
#include "EngineConfiguration.h"

class Engine
{
public:
    Engine(
        const EngineConfiguration& configuration,
        const EngineData& initialData
    );

    void update(double deltaTime);

    EngineData getTelemetry() const;

private:
    EngineConfiguration configuration;
    EngineData data;
};

#endif