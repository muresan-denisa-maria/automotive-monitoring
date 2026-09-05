#ifndef FAULT_SIMULATOR_H
#define FAULT_SIMULATOR_H

#include <random>

enum class FaultType
{
    None,
    CoolingSystem,
    Alternator,
    Brake,
    Battery,
    Engine,
    Clutch,
    Transmission
};

struct FaultState
{
    FaultType type;
    double severity;
    bool active;
};

struct FaultEffects
{
    double coolingSystemHealth;
    double alternatorHealth;
    double brakeHealth;
    double batteryHealth;
    double engineHealth;
    double clutchHealth;
    double transmissionHealth;
};

class FaultSimulator
{
public:
    FaultSimulator();

    void update(double deltaTime);

    FaultState getFaultState() const;

    FaultEffects getFaultEffects() const;

private:
    FaultState faultState;

    double timeSinceStart;
    double timeUntilNextFault;

    std::mt19937 randomGenerator;
};

#endif