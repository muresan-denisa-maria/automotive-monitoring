#include "Clutch.h"


Clutch::Clutch(
    const ClutchConfiguration& configuration,
    const ClutchData& initialData
)
{
    this->configuration = configuration;
    data = initialData;
}


void Clutch::update(
    double deltaTime,
    double engineTorque,
    double engineRpm,
    double transmissionRpm,
    double clutchInput,
    double ambientTemperature
)
{
    if (clutchInput < 0.0)
    {
        clutchInput = 0.0;
    }

    if (clutchInput > 100.0)
    {
        clutchInput = 100.0;
    }

    double clutchEngagement =
        1.0 -
        clutchInput / 100.0;

    data.clutchEngagement =
        clutchEngagement *
        100.0;

    double maximumTransmittedTorque =
        configuration.maximumClutchTorque *
        clutchEngagement;

    double engineAngularVelocity =
        engineRpm *
        2.0 *
        3.14159265359 /
        60.0;

    double transmissionAngularVelocity =
        transmissionRpm *
        2.0 *
        3.14159265359 /
        60.0;

    double slipAngularVelocity =
        engineAngularVelocity -
        transmissionAngularVelocity;

    double synchronizationTorque =
        configuration.slipTorqueCoefficient *
        slipAngularVelocity *
        clutchEngagement;

    double transmittedTorque =
        engineTorque *
        clutchEngagement +
        synchronizationTorque;

    if (transmittedTorque >
        maximumTransmittedTorque)
    {
        transmittedTorque =
            maximumTransmittedTorque;
    }

    if (transmittedTorque <
        -maximumTransmittedTorque)
    {
        transmittedTorque =
            -maximumTransmittedTorque;
    }

    data.transmittedTorque =
        transmittedTorque;

    data.clutchSlip =
        engineRpm -
        transmissionRpm;

    double slipPower =
        transmittedTorque *
        slipAngularVelocity;

    if (slipPower < 0.0)
    {
        slipPower =
            -slipPower;
    }

    double slipEnergy =
        slipPower *
        deltaTime;

    double clutchEnergy =
        slipEnergy *
        configuration.clutchEnergyFraction;

    double temperatureIncrease =
        clutchEnergy /
        (
            configuration.clutchDiscMass *
            configuration.clutchDiscSpecificHeat
        );

    data.clutchDiscTemperature +=
        temperatureIncrease;

    double coolingPower =
        configuration.coolingCoefficient *
        (
            data.clutchDiscTemperature -
            ambientTemperature
        );

    double coolingEnergy =
        coolingPower *
        deltaTime;

    double coolingTemperature =
        coolingEnergy /
        (
            configuration.clutchDiscMass *
            configuration.clutchDiscSpecificHeat
        );

    data.clutchDiscTemperature -=
        coolingTemperature;

    if (data.clutchDiscTemperature <
        ambientTemperature)
    {
        data.clutchDiscTemperature =
            ambientTemperature;
    }
}


ClutchData Clutch::getTelemetry() const
{
    return data;
}