#include "Brake.h"


Brake::Brake(
    const BrakeConfiguration& configuration,
    const BrakeData& initialData
)
{
    this->configuration = configuration;
    this->data = initialData;

    health = 1.0;
}


void Brake::setHealth(
    double health
)
{
    if (health < 0.0)
    {
        health = 0.0;
    }

    if (health > 1.0)
    {
        health = 1.0;
    }

    this->health = health;
}


void Brake::update(
    double deltaTime,
    double vehicleMass,
    double vehicleSpeed,
    double brakeInput,
    double ambientTemperature
)
{
    if (brakeInput < 0.0)
    {
        brakeInput = 0.0;
    }

    if (brakeInput > 100.0)
    {
        brakeInput = 100.0;
    }

    double effectiveMaximumBrakeForce =
        configuration.maximumBrakeForce *
        health;

    double brakeForce =
        (brakeInput / 100.0) *
        effectiveMaximumBrakeForce;

    data.brakeForce =
        brakeForce;

    double deceleration =
        0.0;

    if (vehicleMass > 0.0)
    {
        deceleration =
            brakeForce /
            vehicleMass;
    }

    double newSpeed =
        vehicleSpeed -
        deceleration *
        deltaTime;

    if (newSpeed < 0.0)
    {
        newSpeed = 0.0;
    }

    double kineticEnergyBefore =
        0.5 *
        vehicleMass *
        vehicleSpeed *
        vehicleSpeed;

    double kineticEnergyAfter =
        0.5 *
        vehicleMass *
        newSpeed *
        newSpeed;

    double brakingEnergy =
        kineticEnergyBefore -
        kineticEnergyAfter;

    if (brakingEnergy < 0.0)
    {
        brakingEnergy = 0.0;
    }

    double discEnergy =
        brakingEnergy *
        configuration.brakeEnergyFraction;

    double thermalCapacity =
        configuration.brakeDiscMass *
        configuration.brakeDiscSpecificHeat;

    if (thermalCapacity > 0.0)
    {
        data.brakeDiscTemperature +=
            discEnergy /
            thermalCapacity;
    }

    double coolingPower =
        configuration.coolingCoefficient *
        configuration.brakeDiscArea *
        (
            data.brakeDiscTemperature -
            ambientTemperature
        );

    double coolingEnergy =
        coolingPower *
        deltaTime;

    if (thermalCapacity > 0.0)
    {
        data.brakeDiscTemperature -=
            coolingEnergy /
            thermalCapacity;
    }

    if (data.brakeDiscTemperature <
        ambientTemperature)
    {
        data.brakeDiscTemperature =
            ambientTemperature;
    }

    double wear =
        brakingEnergy *
        configuration.brakePadWearCoefficient;

    data.brakePadWear -=
        wear;

    if (data.brakePadWear < 0.0)
    {
        data.brakePadWear = 0.0;
    }

    data.brakeFluidPressure =
        (brakeInput / 100.0) *
        configuration.maximumBrakePressure *
        health;
}


BrakeData Brake::getTelemetry() const
{
    return data;
}