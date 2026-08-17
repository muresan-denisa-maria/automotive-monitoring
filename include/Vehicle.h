#ifndef VEHICLE_H
#define VEHICLE_H

#include "Engine.h"
#include "Battery.h"
#include "Alternator.h"
#include "Starter.h"
#include "Transmission.h"
#include "Brake.h"
#include "Accelerator.h"
#include "Clutch.h"
#include "FaultSimulator.h"
#include "TelemetryData.h"

class Vehicle
{
public:
    Vehicle(
        const EngineConfiguration& engineConfiguration,
        const EngineData& engineData,

        const BatteryConfiguration& batteryConfiguration,
        const BatteryData& batteryData,

        const AlternatorConfiguration& alternatorConfiguration,
        const AlternatorData& alternatorData,

        const StarterConfiguration& starterConfiguration,
        const StarterData& starterData,

        const TransmissionConfiguration& transmissionConfiguration,
        const TransmissionData& transmissionData,

        const BrakeConfiguration& brakeConfiguration,
        const BrakeData& brakeData,

        const AcceleratorConfiguration& acceleratorConfiguration,
        const AcceleratorData& acceleratorData,

        const ClutchConfiguration& clutchConfiguration,
        const ClutchData& clutchData
    );

    void update(double deltaTime);

    TelemetryData getTelemetry() const;

    FaultState getFaultState() const;

private:
    Engine engine;
    Battery battery;
    Alternator alternator;
    Starter starter;
    Transmission transmission;
    Brake brake;
    Accelerator accelerator;
    Clutch clutch;

    FaultSimulator faultSimulator;
};

#endif