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
                    7
                );

            int randomFault =
                faultDistribution(
                    randomGenerator
                );

            switch (randomFault)
            {
            case 1:
                faultState.type =
                    FaultType::CoolingSystem;
                break;

            case 2:
                faultState.type =
                    FaultType::Alternator;
                break;

            case 3:
                faultState.type =
                    FaultType::Brake;
                break;

            case 4:
                faultState.type =
                    FaultType::Battery;
                break;

            case 5:
                faultState.type =
                    FaultType::Engine;
                break;

            case 6:
                faultState.type =
                    FaultType::Clutch;
                break;

            case 7:
                faultState.type =
                    FaultType::Transmission;
                break;

            default:
                faultState.type =
                    FaultType::None;
                break;
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

    effects.coolingSystemHealth = 1.0;
    effects.alternatorHealth = 1.0;
    effects.brakeHealth = 1.0;
    effects.batteryHealth = 1.0;
    effects.engineHealth = 1.0;
    effects.clutchHealth = 1.0;
    effects.transmissionHealth = 1.0;

    if (!faultState.active)
    {
        return effects;
    }

    switch (faultState.type)
    {
    case FaultType::CoolingSystem:
        effects.coolingSystemHealth =
            1.0 -
            0.90 *
            faultState.severity;
        break;

    case FaultType::Alternator:
        effects.alternatorHealth =
            1.0 -
            0.95 *
            faultState.severity;
        break;

    case FaultType::Brake:
        effects.brakeHealth =
            1.0 -
            0.75 *
            faultState.severity;
        break;

    case FaultType::Battery:
        effects.batteryHealth =
            1.0 -
            0.85 *
            faultState.severity;
        break;

    case FaultType::Engine:
        effects.engineHealth =
            1.0 -
            0.70 *
            faultState.severity;
        break;

    case FaultType::Clutch:
        effects.clutchHealth =
            1.0 -
            0.90 *
            faultState.severity;
        break;

    case FaultType::Transmission:
        effects.transmissionHealth =
            1.0 -
            0.70 *
            faultState.severity;
        break;

    default:
        break;
    }

    if (effects.coolingSystemHealth < 0.10)
    {
        effects.coolingSystemHealth = 0.10;
    }

    if (effects.alternatorHealth < 0.05)
    {
        effects.alternatorHealth = 0.05;
    }

    if (effects.brakeHealth < 0.25)
    {
        effects.brakeHealth = 0.25;
    }

    if (effects.batteryHealth < 0.15)
    {
        effects.batteryHealth = 0.15;
    }

    if (effects.engineHealth < 0.30)
    {
        effects.engineHealth = 0.30;
    }

    if (effects.clutchHealth < 0.10)
    {
        effects.clutchHealth = 0.10;
    }

    if (effects.transmissionHealth < 0.30)
    {
        effects.transmissionHealth = 0.30;
    }

    return effects;
}