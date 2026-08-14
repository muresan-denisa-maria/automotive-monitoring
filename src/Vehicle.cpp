#include "Vehicle.h"

Vehicle::Vehicle(
    const EngineConfiguration& engineConfiguration,
    const EngineData& engineData,
    const BatteryData& batteryData,
    const TransmissionData& transmissionData,
    const BrakeData& brakeData
)
    : engine(engineConfiguration, engineData),
      battery(batteryData),
      transmission(transmissionData),
      brake(brakeData)
{
}

void Vehicle::update(double deltaTime)
{
    engine.update(deltaTime);
    battery.update(deltaTime);
    transmission.update(deltaTime);
    brake.update(deltaTime);
}

TelemetryData Vehicle::getTelemetry() const
{
    TelemetryData telemetry;

    telemetry.engine = engine.getTelemetry();
    telemetry.battery = battery.getTelemetry();
    telemetry.transmission = transmission.getTelemetry();
    telemetry.brake = brake.getTelemetry();

    return telemetry;
}