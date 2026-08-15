#include "Brake.h"


Brake::Brake(
    const BrakeConfiguration& configuration,
    const BrakeData& initialData
)
{
    this->configuration = configuration;
    data = initialData;
}


void Brake::update(
    double deltaTime,
    double vehicleMass,
    double vehicleSpeed,
    double brakeInput,
    double ambientTemperature
)
{
    // Calcularea fortei de franare
    double brakeForce =
        (brakeInput / 100.0) *
        configuration.maximumBrakeForce;


    // Calcularea deceleratiei folosind F = m * a
    double deceleration =
        brakeForce /
        vehicleMass;


    // Calcularea vitezei dupa franare
    double initialSpeed =
        vehicleSpeed;

    double newSpeed =
        initialSpeed -
        deceleration * deltaTime;

    if (newSpeed < 0)
    {
        newSpeed = 0;
    }


    // Calcularea energiei cinetice inainte de franare
    double initialKineticEnergy =
        0.5 *
        vehicleMass *
        initialSpeed *
        initialSpeed;


    // Calcularea energiei cinetice dupa franare
    double finalKineticEnergy =
        0.5 *
        vehicleMass *
        newSpeed *
        newSpeed;


    // Energia transformata in timpul franarii
    double brakingEnergy =
        initialKineticEnergy -
        finalKineticEnergy;


    // Energia care ajunge la sistemul de franare
    double brakeEnergy =
        brakingEnergy *
        configuration.brakeEnergyFraction;


    // Impartim energia intre cele patru discuri
    double discEnergy =
        brakeEnergy / 4.0;


    // Calcularea cresterii temperaturii discului
    // Q = m * c * deltaT
    double temperatureIncrease =
        discEnergy /
        (
            configuration.brakeDiscMass *
            configuration.brakeDiscSpecificHeat
        );

    data.brakeDiscTemperature +=
        temperatureIncrease;


    // Calcularea racirii discului
    // P = h * A * (Tdisc - Tambient)
    double coolingPower =
        configuration.coolingCoefficient *
        configuration.brakeDiscArea *
        (
            data.brakeDiscTemperature -
            ambientTemperature
        );


    // Energia pierduta prin racire
    double coolingEnergy =
        coolingPower * deltaTime;


    // Scaderea temperaturii datorita racirii
    double coolingTemperature =
        coolingEnergy /
        (
            configuration.brakeDiscMass *
            configuration.brakeDiscSpecificHeat
        );

    data.brakeDiscTemperature -=
        coolingTemperature;


    // Temperatura discului nu poate fi mai mica decat temperatura mediului
    if (data.brakeDiscTemperature <
        ambientTemperature)
    {
        data.brakeDiscTemperature =
            ambientTemperature;
    }


    // Calcularea uzurii placutelor
    double padWear =
        brakeEnergy *
        configuration.brakePadWearCoefficient;

    data.brakePadWear -=
        padWear;


    // Uzura nu poate fi mai mica de 0
    if (data.brakePadWear < 0)
    {
        data.brakePadWear = 0;
    }


    // Calcularea presiunii lichidului de frana
    data.brakeFluidPressure =
        (brakeInput / 100.0) *
        configuration.maximumBrakePressure;
}


BrakeData Brake::getTelemetry() const
{
    return data;
}