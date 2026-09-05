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

    const TransmissionConfiguration& transmissionConfiguration,
    const TransmissionData& transmissionData,

    const BrakeConfiguration& brakeConfiguration,
    const BrakeData& brakeData,

    const AcceleratorConfiguration& acceleratorConfiguration,
    const AcceleratorData& acceleratorData,

    const ClutchConfiguration& clutchConfiguration,
    const ClutchData& clutchData
)
    : engine(
        engineConfiguration,
        engineData
    ),

      battery(
        batteryConfiguration,
        batteryData
    ),

      alternator(
        alternatorConfiguration,
        alternatorData
    ),

      starter(
        starterConfiguration,
        starterData
    ),

      transmission(
        transmissionConfiguration,
        transmissionData
    ),

      brake(
        brakeConfiguration,
        brakeData
    ),

      accelerator(
        acceleratorConfiguration,
        acceleratorData
    ),

      clutch(
        clutchConfiguration,
        clutchData
    )
{
    detectedFault =
        DetectedFaultType::None;
}


void Vehicle::update(
    double deltaTime,
    const VehicleInput& input
)
{
    faultSimulator.update(
        deltaTime
    );


    FaultEffects faultEffects =
        faultSimulator.getFaultEffects();


    engine.setCoolingSystemHealth(
        faultEffects.coolingSystemHealth
    );


    engine.setHealth(
        faultEffects.engineHealth
    );


    battery.setHealth(
        faultEffects.batteryHealth
    );


    alternator.setHealth(
        faultEffects.alternatorHealth
    );


    brake.setHealth(
        faultEffects.brakeHealth
    );


    clutch.setHealth(
        faultEffects.clutchHealth
    );


    transmission.setHealth(
        faultEffects.transmissionHealth
    );


    accelerator.update(
        deltaTime,
        input.acceleratorInput
    );


    starter.update(
        deltaTime,
        battery.getTelemetry().batteryVoltage,
        input.startCommand,
        20.0
    );


    engine.update(
        deltaTime,
        accelerator.getTelemetry().throttlePosition,
        clutch.getTelemetry().transmittedTorque,
        input.startCommand,
        20.0
    );


    alternator.update(
        deltaTime,
        engine.getTelemetry().rpm
    );


    double electricalLoad =
        35.0;


    battery.update(
        deltaTime,
        alternator.getTelemetry().alternatorCurrent,
        starter.getTelemetry().starterCurrent,
        electricalLoad,
        20.0
    );


    clutch.update(
        deltaTime,
        engine.getTelemetry().engineTorque,
        engine.getTelemetry().rpm,
        transmission.getTelemetry().transmissionRpm,
        input.clutchInput,
        20.0
    );


    brake.update(
        deltaTime,
        1500.0,
        transmission.getTelemetry().vehicleSpeed,
        input.brakeInput,
        20.0
    );


    transmission.update(
        deltaTime,
        clutch.getTelemetry().transmittedTorque,
        input.gearPosition,
        1500.0,
        brake.getTelemetry().brakeForce
    );


    DetectedFaultType currentDetectedFault =
        faultDetector.detect(
            getTelemetry(),
            deltaTime,
            input.acceleratorInput,
            input.brakeInput,
            1500.0
        );


    if (currentDetectedFault !=
        DetectedFaultType::None)
    {
        detectedFault =
            currentDetectedFault;
    }
}


TelemetryData Vehicle::getTelemetry() const
{
    TelemetryData telemetry{};


    telemetry.engine =
        engine.getTelemetry();


    telemetry.battery =
        battery.getTelemetry();


    telemetry.alternator =
        alternator.getTelemetry();


    telemetry.starter =
        starter.getTelemetry();


    telemetry.transmission =
        transmission.getTelemetry();


    telemetry.brake =
        brake.getTelemetry();


    telemetry.accelerator =
        accelerator.getTelemetry();


    telemetry.clutch =
        clutch.getTelemetry();


    return telemetry;
}


FaultState Vehicle::getFaultState() const
{
    return faultSimulator.getFaultState();
}


DetectedFaultType Vehicle::getDetectedFault() const
{
    return detectedFault;
}