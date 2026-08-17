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
    // Limitarea inputului ambreiajului intre 0% si 100%
    if (clutchInput < 0.0)
    {
        clutchInput = 0.0;
    }

    if (clutchInput > 100.0)
    {
        clutchInput = 100.0;
    }


    // Calcularea gradului de cuplare al ambreiajului
    double clutchEngagement =
        1.0 -
        (clutchInput / 100.0);


    data.clutchEngagement =
        clutchEngagement * 100.0;


    // Calcularea cuplului maxim transmis
    double maximumTransmittedTorque =
        configuration.maximumClutchTorque *
        clutchEngagement;


    // Cuplul transmis nu poate depasi cuplul motorului
    double transmittedTorque =
        engineTorque;

    if (transmittedTorque >
        maximumTransmittedTorque)
    {
        transmittedTorque =
            maximumTransmittedTorque;
    }


    if (transmittedTorque < 0.0)
    {
        transmittedTorque = 0.0;
    }


    data.transmittedTorque =
        transmittedTorque;


    // Calcularea diferentei de turatie dintre motor si transmisie
    double rpmDifference =
        engineRpm -
        transmissionRpm;


    data.clutchSlip =
        rpmDifference;


    // Conversia RPM in rad/s
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


    // Diferenta de viteza unghiulara
    double slipAngularVelocity =
        engineAngularVelocity -
        transmissionAngularVelocity;


    if (slipAngularVelocity < 0.0)
    {
        slipAngularVelocity =
            -slipAngularVelocity;
    }


    // Calcularea puterii pierdute prin alunecare
    // P = T * omega
    double slipPower =
        transmittedTorque *
        slipAngularVelocity;


    // Energia pierduta prin alunecare
    double slipEnergy =
        slipPower *
        deltaTime;


    // Energia care ajunge in discul de ambreiaj
    double clutchEnergy =
        slipEnergy *
        configuration.clutchEnergyFraction;


    // Calcularea cresterii temperaturii discului
    // Q = m * c * deltaT
    double temperatureIncrease =
        clutchEnergy /
        (
            configuration.clutchDiscMass *
            configuration.clutchDiscSpecificHeat
        );

    data.clutchDiscTemperature +=
        temperatureIncrease;


    // Calcularea racirii discului
    // P = h * (Tclutch - Tambient)
    double coolingPower =
        configuration.coolingCoefficient *
        (
            data.clutchDiscTemperature -
            ambientTemperature
        );


    // Energia pierduta prin racire
    double coolingEnergy =
        coolingPower *
        deltaTime;


    // Scaderea temperaturii datorita racirii
    double coolingTemperature =
        coolingEnergy /
        (
            configuration.clutchDiscMass *
            configuration.clutchDiscSpecificHeat
        );

    data.clutchDiscTemperature -=
        coolingTemperature;


    // Temperatura discului nu poate fi mai mica decat temperatura mediului
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