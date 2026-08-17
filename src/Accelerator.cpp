#include "Accelerator.h"


Accelerator::Accelerator(
    const AcceleratorConfiguration& configuration,
    const AcceleratorData& initialData
)
{
    this->configuration = configuration;
    data = initialData;
}


void Accelerator::update(
    double deltaTime,
    double acceleratorInput
)
{
    // Limitarea inputului acceleratorului intre 0% si 100%
    if (acceleratorInput < 0.0)
    {
        acceleratorInput = 0.0;
    }

    if (acceleratorInput > 100.0)
    {
        acceleratorInput = 100.0;
    }


    // Calcularea diferentei dintre input si pozitia actuala
    double throttleDifference =
        acceleratorInput -
        data.throttlePosition;


    // Calcularea vitezei de modificare a clapetei
    double throttleRate =
        configuration.maximumThrottle /
        configuration.throttleResponseTime;


    // Calcularea modificarii pozitiei clapetei
    double throttleChange =
        throttleRate *
        deltaTime;


    // Actualizarea pozitiei clapetei
    if (throttleDifference > throttleChange)
    {
        data.throttlePosition +=
            throttleChange;
    }
    else if (throttleDifference < -throttleChange)
    {
        data.throttlePosition -=
            throttleChange;
    }
    else
    {
        data.throttlePosition =
            acceleratorInput;
    }


    // Pozitia clapetei nu poate depasi valoarea maxima
    if (data.throttlePosition >
        configuration.maximumThrottle)
    {
        data.throttlePosition =
            configuration.maximumThrottle;
    }


    // Pozitia clapetei nu poate fi negativa
    if (data.throttlePosition < 0.0)
    {
        data.throttlePosition = 0.0;
    }
}


AcceleratorData Accelerator::getTelemetry() const
{
    return data;
}