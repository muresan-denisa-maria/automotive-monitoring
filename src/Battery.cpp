#include "Battery.h"


Battery::Battery(
    const BatteryConfiguration& configuration,
    const BatteryData& initialData
)
{
    this->configuration = configuration;
    data = initialData;
}


void Battery::update(
    double deltaTime,
    double alternatorCurrent,
    double starterCurrent,
    double electricalLoad,
    double ambientTemperature
)
{
    // Calcularea curentului bateriei
    // Curentul alternatorului incarca bateria
    // Curentul starterului si consumatorii descarca bateria
    double batteryCurrent =
        electricalLoad +
        starterCurrent -
        alternatorCurrent;

    data.batteryCurrent =
        batteryCurrent;


    // Calcularea tensiunii in gol in functie de SOC
    double openCircuitVoltage =
        configuration.nominalVoltage *
        (
            0.9 +
            0.1 *
            (
                data.batteryStateOfCharge /
                100.0
            )
        );


    // Calcularea tensiunii bateriei
    // V = Voc - I * R
    data.batteryVoltage =
        openCircuitVoltage -
        data.batteryCurrent *
        configuration.internalResistance;


    // Calcularea pierderilor interne
    // P = I^2 * R
    double internalPowerLoss =
        data.batteryCurrent *
        data.batteryCurrent *
        configuration.internalResistance;


    // Energia pierduta prin rezistenta interna
    double internalEnergyLoss =
        internalPowerLoss *
        deltaTime;


    // Calcularea cresterii temperaturii
    // Q = C * deltaT
    double temperatureIncrease =
        internalEnergyLoss /
        configuration.thermalCapacity;

    data.batteryTemperature +=
        temperatureIncrease;


    // Calcularea racirii bateriei
    // P = h * (T - Tambient)
    double coolingPower =
        configuration.coolingCoefficient *
        (
            data.batteryTemperature -
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

    data.batteryTemperature -=
        coolingTemperature;


    // Temperatura bateriei nu poate fi mai mica decat temperatura mediului
    if (data.batteryTemperature <
        ambientTemperature)
    {
        data.batteryTemperature =
            ambientTemperature;
    }


    // Calcularea modificarii starii de incarcare
    double chargeChange =
        (
            data.batteryCurrent *
            deltaTime
        ) /
        (
            3600.0 *
            configuration.capacityAh
        );


    data.batteryStateOfCharge -=
        chargeChange * 100.0;


    // State of charge nu poate fi mai mare de 100%
    if (data.batteryStateOfCharge > 100.0)
    {
        data.batteryStateOfCharge = 100.0;
    }


    // State of charge nu poate fi mai mic de 0%
    if (data.batteryStateOfCharge < 0.0)
    {
        data.batteryStateOfCharge = 0.0;
    }


    // Curentul nu poate depasi limita maxima a bateriei
    if (data.batteryCurrent >
        configuration.maximumCurrent)
    {
        data.batteryCurrent =
            configuration.maximumCurrent;
    }


    // Curentul nu poate fi mai mic decat limita negativa
    if (data.batteryCurrent <
        -configuration.maximumCurrent)
    {
        data.batteryCurrent =
            -configuration.maximumCurrent;
    }


    // Tensiunea bateriei nu poate fi negativa
    if (data.batteryVoltage < 0.0)
    {
        data.batteryVoltage = 0.0;
    }
}


BatteryData Battery::getTelemetry() const
{
    return data;
}