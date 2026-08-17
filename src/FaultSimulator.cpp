#include "FaultSimulator.h"

#include <random>


FaultSimulator::FaultSimulator()
{
    faultState.type = FaultType::None;
    faultState.severity = 0.0;
    faultState.active = false;

    timeSinceStart = 0.0;

    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());

    std::uniform_real_distribution<double> distribution(
        20.0,
        60.0
    );

    timeUntilNextFault =
        distribution(generator);
}


void FaultSimulator::update(double deltaTime)
{
    timeSinceStart += deltaTime;

    if (faultState.active)
    {
        faultState.severity +=
            0.001 * deltaTime;

        if (faultState.severity > 1.0)
        {
            faultState.severity = 1.0;
        }

        return;
    }


    if (timeSinceStart >= timeUntilNextFault)
    {
        std::random_device randomDevice;
        std::mt19937 generator(randomDevice());

        std::uniform_int_distribution<int> faultDistribution(
            1,
            7
        );

        int selectedFault =
            faultDistribution(generator);


        switch (selectedFault)
        {
        case 1:
            faultState.type =
                FaultType::CoolingSystem;
            break;

        case 2:
            faultState.type =
                FaultType::Battery;
            break;

        case 3:
            faultState.type =
                FaultType::Alternator;
            break;

        case 4:
            faultState.type =
                FaultType::Brake;
            break;

        case 5:
            faultState.type =
                FaultType::Clutch;
            break;

        case 6:
            faultState.type =
                FaultType::Engine;
            break;

        case 7:
            faultState.type =
                FaultType::Transmission;
            break;
        }


        faultState.severity = 0.01;
        faultState.active = true;
    }
}


FaultState FaultSimulator::getFaultState() const
{
    return faultState;
}