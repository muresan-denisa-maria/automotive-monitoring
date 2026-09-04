#ifndef FAULT_SIMULATOR_H
#define FAULT_SIMULATOR_H

#include <random>

enum class FaultType
{
    None,
    CoolingSystem,
    Alternator,
    Brake
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