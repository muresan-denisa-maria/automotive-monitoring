#include "Transmission.h"


Transmission::Transmission(
    const TransmissionConfiguration& configuration,
    const TransmissionData& initialData
)
{
    this->configuration =
        configuration;

    data =
        initialData;

    health =
        1.0;
}


void Transmission::setHealth(
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

    this->health =
        health;
}


void Transmission::update(
    double deltaTime,
    double clutchTorque,
    int gearPosition,
    double vehicleMass,
    double brakeForce
)
{
    double gearRatio =
        0.0;


    switch (gearPosition)
    {
    case 1:
        gearRatio =
            configuration.firstGearRatio;
        break;

    case 2:
        gearRatio =
            configuration.secondGearRatio;
        break;

    case 3:
        gearRatio =
            configuration.thirdGearRatio;
        break;

    case 4:
        gearRatio =
            configuration.fourthGearRatio;
        break;

    case 5:
        gearRatio =
            configuration.fifthGearRatio;
        break;

    default:
        gearRatio =
            0.0;

        gearPosition =
            0;
        break;
    }


    data.transmissionGearPosition =
        gearPosition;


    double effectiveEfficiency =
        configuration.transmissionEfficiency *
        (
            0.4 +
            0.6 * health
        );


    if (effectiveEfficiency < 0.0)
    {
        effectiveEfficiency = 0.0;
    }

    if (effectiveEfficiency > 1.0)
    {
        effectiveEfficiency = 1.0;
    }


    double tractionForce =
        0.0;


    if (gearRatio > 0.0 &&
        configuration.wheelRadius > 0.0)
    {
        double wheelTorque =
            clutchTorque *
            gearRatio *
            configuration.finalDriveRatio *
            effectiveEfficiency;


        tractionForce =
            wheelTorque /
            configuration.wheelRadius;
    }


    double netForce =
        tractionForce -
        brakeForce;


    double acceleration =
        0.0;


    if (vehicleMass > 0.0)
    {
        acceleration =
            netForce /
            vehicleMass;
    }


    data.vehicleSpeed +=
        acceleration *
        deltaTime;


    if (data.vehicleSpeed < 0.0)
    {
        data.vehicleSpeed =
            0.0;
    }


    double wheelAngularVelocity =
        0.0;


    if (configuration.wheelRadius > 0.0)
    {
        wheelAngularVelocity =
            data.vehicleSpeed /
            configuration.wheelRadius;
    }


    data.wheelRpm =
        wheelAngularVelocity *
        60.0 /
        (
            2.0 *
            3.14159265359
        );


    if (gearRatio > 0.0)
    {
        data.transmissionRpm =
            data.wheelRpm *
            configuration.finalDriveRatio *
            gearRatio;
    }
    else
    {
        data.transmissionRpm =
            0.0;
    }


    double transmissionAngularVelocity =
        data.transmissionRpm *
        2.0 *
        3.14159265359 /
        60.0;


    double inputPower =
        clutchTorque *
        transmissionAngularVelocity;


    if (inputPower < 0.0)
    {
        inputPower =
            -inputPower;
    }


    double powerLoss =
        inputPower *
        (
            1.0 -
            effectiveEfficiency
        );


    double coolingPower =
        configuration.coolingCoefficient *
        (
            data.transmissionTemperature -
            configuration.ambientTemperature
        );


    double netHeatPower =
        powerLoss -
        coolingPower;


    if (configuration.thermalCapacity > 0.0)
    {
        data.transmissionTemperature +=
            (
                netHeatPower *
                deltaTime
            ) /
            configuration.thermalCapacity;
    }


    if (data.transmissionTemperature <
        configuration.ambientTemperature)
    {
        data.transmissionTemperature =
            configuration.ambientTemperature;
    }
}


TransmissionData Transmission::getTelemetry() const
{
    return data;
}