#include "Transmission.h"


Transmission::Transmission(
    const TransmissionConfiguration& configuration,
    const TransmissionData& initialData
)
{
    this->configuration = configuration;
    data = initialData;
}


void Transmission::update(
    double deltaTime,
    double engineRpm,
    double clutchTorque
)
{
    // Verificam treapta de viteza
    int gear =
        static_cast<int>(
            data.transmissionGearPosition
        );


    double gearRatio = 0.0;


    switch (gear)
    {
    case 1:
        gearRatio = configuration.firstGearRatio;
        break;

    case 2:
        gearRatio = configuration.secondGearRatio;
        break;

    case 3:
        gearRatio = configuration.thirdGearRatio;
        break;

    case 4:
        gearRatio = configuration.fourthGearRatio;
        break;

    case 5:
        gearRatio = configuration.fifthGearRatio;
        break;

    default:
        gearRatio = 0.0;
        break;
    }


    // Calculam turatia transmisiei
    if (gearRatio > 0.0)
    {
        data.transmissionRpm =
            engineRpm /
            gearRatio;
    }
    else
    {
        data.transmissionRpm = 0.0;
    }


    // Calculam turatia rotii
    if (configuration.finalDriveRatio > 0.0)
    {
        data.wheelRpm =
            data.transmissionRpm /
            configuration.finalDriveRatio;
    }
    else
    {
        data.wheelRpm = 0.0;
    }


    // Calculam viteza masinii
    // v = omega * r

    double wheelAngularVelocity =
        data.wheelRpm *
        2.0 *
        3.14159265359 /
        60.0;


    double vehicleSpeedMetersPerSecond =
        wheelAngularVelocity *
        configuration.wheelRadius;


    // m/s -> km/h
    data.vehicleSpeed =
        vehicleSpeedMetersPerSecond *
        3.6;


    // Temperatura transmisiei
    double transmissionPower =
        clutchTorque *
        data.transmissionRpm *
        2.0 *
        3.14159265359 /
        60.0;


    double powerLoss =
        transmissionPower *
        (
            1.0 -
            configuration.transmissionEfficiency
        );


    // Pentru moment folosim o aproximare simpla
    data.transmissionTemperature +=
        powerLoss *
        deltaTime *
        0.001;


    // Temperatura nu trebuie sa fie negativa
    if (data.transmissionTemperature < 0.0)
    {
        data.transmissionTemperature = 0.0;
    }
}


TransmissionData Transmission::getTelemetry() const
{
    return data;
}