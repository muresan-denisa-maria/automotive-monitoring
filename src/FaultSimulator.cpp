#include "FaultSimulator.h"


FaultSimulator::FaultSimulator()
    : randomGenerator(
        std::random_device{}()
    )
{
    faultState.type =
        FaultType::None;

    faultState.severity =
        0.0;

    faultState.active =
        false;

    timeSinceStart =
        0.0;

    std::uniform_real_distribution<double>
        timeDistribution(
            8.0,
            12.0
        );

    timeUntilNextFault =
        timeDistribution(
            randomGenerator
        );
}


void FaultSimulator::update(
    double deltaTime
)
{
    timeSinceStart +=
        deltaTime;

    if (!faultState.active)
    {
        if (timeSinceStart >=
            timeUntilNextFault)
        {
            std::uniform_int_distribution<int>
                faultDistribution(
                    1,
                    3
                );

            int randomFault =
                faultDistribution(
                    randomGenerator
                );

            if (randomFault == 1)
            {
                faultState.type =
                    FaultType::CoolingSystem;
            }
            else if (randomFault == 2)
            {
                faultState.type =
                    FaultType::Alternator;
            }
            else
            {
                faultState.type =
                    FaultType::Brake;
            }

            faultState.active =
                true;

            faultState.severity =
                0.10;
        }
    }
    else
    {
        faultState.severity +=
            0.03 *
            deltaTime;

        if (faultState.severity > 1.0)
        {
            faultState.severity =
                1.0;
        }
    }
}


FaultState FaultSimulator::getFaultState() const
{
    return faultState;
}


FaultEffects FaultSimulator::getFaultEffects() const
{
    FaultEffects effects{};

    effects.coolingSystemHealth =
        1.0;

    effects.alternatorHealth =
        1.0;

    effects.brakeHealth =
        1.0;

    if (!faultState.active)
    {
        return effects;
    }

    if (faultState.type ==
        FaultType::CoolingSystem)
    {
        effects.coolingSystemHealth =
            1.0 -
            0.90 *
            faultState.severity;
    }
    else if (faultState.type ==
             FaultType::Alternator)
    {
        effects.alternatorHealth =
            1.0 -
            0.95 *
            faultState.severity;
    }
    else if (faultState.type ==
             FaultType::Brake)
    {
        effects.brakeHealth =
            1.0 -
            0.75 *
            faultState.severity;
    }

    if (effects.coolingSystemHealth < 0.10)
    {
        effects.coolingSystemHealth =
            0.10;
    }

    if (effects.alternatorHealth < 0.05)
    {
        effects.alternatorHealth =
            0.05;
    }

    if (effects.brakeHealth < 0.25)
    {
        effects.brakeHealth =
            0.25;
    }

    return effects;
}