#ifndef VEHICLE_H
#define VEHICLE_H

#include "Engine.h"
#include "Battery.h"
#include "Transmission.h"
#include "Brake.h"
#include "TelemetryData.h"

class Vehicle
{
public:
    Vehicle(
        const EngineConfiguration& engineConfiguration,
        const EngineData& engineData,
        const BatteryData& batteryData,
        const TransmissionData& transmissionData,
        const BrakeData& brakeData
    );

    void update(double deltaTime);

    TelemetryData getTelemetry() const;

private:
    Engine engine;
    Battery battery;
    Transmission transmission;
    Brake brake;
};

#endif