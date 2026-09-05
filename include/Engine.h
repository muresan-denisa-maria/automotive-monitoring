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

    void update(
        double deltaTime,
        double throttlePosition,
        double loadTorque,
        bool startCommand,
        double ambientTemperature
    );

    void setCoolingSystemHealth(
        double health
    );

    void setHealth(
        double health
    );

    EngineData getTelemetry() const;

private:
    EngineConfiguration configuration;
    EngineData data;

    double coolingSystemHealth;
    double health;
};

#endif