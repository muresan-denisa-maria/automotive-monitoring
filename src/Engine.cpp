#include "Engine.h"

Engine::Engine(
    const EngineConfiguration& configuration,
    const EngineData& initialData
)
{
    this->configuration = configuration;
    this->data = initialData;
}

void Engine::update(double deltaTime)
{
    // Vom implementa aici simularea motorului.
}

EngineData Engine::getTelemetry() const
{
    return data;
}