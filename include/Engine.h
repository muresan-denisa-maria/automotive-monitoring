#ifndef ENGINE_H
#define ENGINE_H

#include "TelemetryData.h"
class Engine
{
public:
    Engine();

    void update(double deltaTime);

    EngineData getTelemetry() const;

private:
    EngineData data;
};

#endif