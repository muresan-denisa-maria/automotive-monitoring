#include "Starter.h"


Starter::Starter(
    const StarterConfiguration& configuration,
    const StarterData& initialData
)
{
    this->configuration = configuration;
    data = initialData;
}


void Starter::update(
    double deltaTime,
    double batteryVoltage,
    bool startCommand,
    double ambientTemperature
)
{
    // Verificarea daca exista comanda de pornire
    if (startCommand &&
        batteryVoltage >= configuration.minimumVoltage)
    {
        // Calcularea curentului consumat de starter
        data.starterCurrent =
            configuration.maximumCurrent;
    }
    else
    {
        data.starterCurrent = 0.0;
    }


    // Tensiunea starterului este tensiunea bateriei
    data.starterVoltage =
        batteryVoltage;


    // Calcularea puterii electrice consumate
    // P = V * I
    double electricalPower =
        data.starterVoltage *
        data.starterCurrent;


    // Calcularea puterii mecanice
    double mechanicalPower =
        electricalPower *
        configuration.efficiency;


    // Calcularea pierderilor sub forma de caldura
    double powerLoss =
        electricalPower -
        mechanicalPower;


    // Energia transformata in caldura
    double heatEnergy =
        powerLoss *
        deltaTime;


    // Calcularea cresterii temperaturii
    // Q = C * deltaT
    double temperatureIncrease =
        heatEnergy /
        configuration.thermalCapacity;

    data.starterTemperature +=
        temperatureIncrease;


    // Calcularea racirii starterului
    // P = h * (T - Tambient)
    double coolingPower =
        configuration.coolingCoefficient *
        (
            data.starterTemperature -
            ambientTemperature
        );


    // Energia pierduta prin racire
    double coolingEnergy =
        coolingPower *
        deltaTime;


    // Scaderea temperaturii datorita racirii
    double coolingTemperature =
        coolingEnergy /
        configuration.thermalCapacity;

    data.starterTemperature -=
        coolingTemperature;


    // Temperatura starterului nu poate fi mai mica decat temperatura mediului
    if (data.starterTemperature <
        ambientTemperature)
    {
        data.starterTemperature =
            ambientTemperature;
    }


    // Curentul nu poate depasi valoarea maxima
    if (data.starterCurrent >
        configuration.maximumCurrent)
    {
        data.starterCurrent =
            configuration.maximumCurrent;
    }


    // Tensiunea nu poate fi negativa
    if (data.starterVoltage < 0.0)
    {
        data.starterVoltage = 0.0;
    }
}


StarterData Starter::getTelemetry() const
{
    return data;
}