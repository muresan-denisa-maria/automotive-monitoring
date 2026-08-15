#include "Alternator.h"


Alternator::Alternator(
    const AlternatorConfiguration& configuration,
    const AlternatorData& initialData
)
{
    this->configuration = configuration;
    data = initialData;
}


void Alternator::update(
    double deltaTime,
    double engineRpm
)
{
    // Calcularea curentului produs de alternator in functie de RPM
    double rpmRatio =
        engineRpm /
        configuration.maximumRpm;

    if (rpmRatio > 1.0)
    {
        rpmRatio = 1.0;
    }

    if (rpmRatio < 0.0)
    {
        rpmRatio = 0.0;
    }

    data.alternatorCurrent =
        rpmRatio *
        configuration.maximumCurrent;


    // Calcularea tensiunii alternatorului
    data.alternatorVoltage =
        configuration.nominalVoltage;


    // Calcularea puterii produse de alternator
    // P = V * I
    double electricalPower =
        data.alternatorVoltage *
        data.alternatorCurrent;


    // Calcularea puterii pierdute
    double powerLoss =
        electricalPower *
        (
            1.0 -
            configuration.efficiency
        );


    // Calcularea energiei pierdute
    double energyLoss =
        powerLoss *
        deltaTime;


    // Calcularea cresterii temperaturii
    // Q = C * deltaT
    double temperatureIncrease =
        energyLoss /
        configuration.thermalCapacity;

    data.alternatorTemperature +=
        temperatureIncrease;


    // Calcularea racirii alternatorului
    // P = h * (T - Tambient)
    double coolingPower =
        configuration.coolingCoefficient *
        (
            data.alternatorTemperature -
            configuration.ambientTemperature
        );


    // Energia pierduta prin racire
    double coolingEnergy =
        coolingPower *
        deltaTime;


    // Scaderea temperaturii datorita racirii
    double coolingTemperature =
        coolingEnergy /
        configuration.thermalCapacity;

    data.alternatorTemperature -=
        coolingTemperature;


    // Temperatura alternatorului nu poate fi mai mica decat temperatura mediului
    if (data.alternatorTemperature <
        configuration.ambientTemperature)
    {
        data.alternatorTemperature =
            configuration.ambientTemperature;
    }


    // Curentul nu poate depasi valoarea maxima
    if (data.alternatorCurrent >
        configuration.maximumCurrent)
    {
        data.alternatorCurrent =
            configuration.maximumCurrent;
    }
}


AlternatorData Alternator::getTelemetry() const
{
    return data;
}