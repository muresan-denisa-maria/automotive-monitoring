#ifndef FAULT_SIMULATOR_H
#define FAULT_SIMULATOR_H

enum class FaultType
{
    None,
    CoolingSystem,
    Battery,
    Alternator,
    Brake,
    Clutch,
    Engine,
    Transmission
};

struct FaultState
{
    FaultType type;
    double severity;
    bool active;
};

class FaultSimulator
{
public:
    FaultSimulator();

    void update(double deltaTime);

    FaultState getFaultState() const;

private:
    FaultState faultState;

    double timeSinceStart;
    double timeUntilNextFault;
};

#endif