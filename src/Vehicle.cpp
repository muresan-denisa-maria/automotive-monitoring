#include "Vehicle.h"


Vehicle::Vehicle(
    const EngineConfiguration& engineConfiguration,
    const EngineData& engineData,

    const BatteryConfiguration& batteryConfiguration,
    const BatteryData& batteryData,

    const AlternatorConfiguration& alternatorConfiguration,
    const AlternatorData& alternatorData,

    const StarterConfiguration& starterConfiguration,
    const StarterData& starterData,

    const TransmissionData& transmissionData,

    const BrakeConfiguration& brakeConfiguration,
    const BrakeData& brakeData,

    const AcceleratorConfiguration& acceleratorConfiguration,
    const AcceleratorData& acceleratorData,

    const ClutchConfiguration& clutchConfiguration,
    const ClutchData& clutchData
)
    : engine(engineConfiguration, engineData),
      battery(batteryConfiguration, batteryData),
      alternator(alternatorConfiguration, alternatorData),
      starter(starterConfiguration, starterData),
      transmission(transmissionData),
      brake(brakeConfiguration, brakeData),
      accelerator(acceleratorConfiguration, acceleratorData),
      clutch(clutchConfiguration, clutchData)
{
}


void Vehicle::update(double deltaTime)
{
    faultSimulator.update(deltaTime);

    // Aici vom actualiza toate componentele masinii.
    // Valorile concrete folosite aici trebuie sa corespunda
    // semnaturilor actuale ale claselor tale.
}


TelemetryData Vehicle::getTelemetry() const
{
    TelemetryData telemetry;

    telemetry.engine = engine.getTelemetry();
    telemetry.battery = battery.getTelemetry();
    telemetry.alternator = alternator.getTelemetry();
    telemetry.starter = starter.getTelemetry();
    telemetry.transmission = transmission.getTelemetry();
    telemetry.brake = brake.getTelemetry();
    telemetry.accelerator = accelerator.getTelemetry();
    telemetry.clutch = clutch.getTelemetry();

    return telemetry;
}


FaultState Vehicle::getFaultState() const
{
    return faultSimulator.getFaultState();
}