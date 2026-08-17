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
}


void Vehicle::update(double deltaTime)
{
    // Simularea defectelor
    faultSimulator.update(deltaTime);


    // =====================================================
    // 1. ACCELERATOR
    // =====================================================

    double acceleratorInput = 0.0;

    accelerator.update(
        deltaTime,
        acceleratorInput
    );


    // =====================================================
    // 2. ENGINE
    // =====================================================

    engine.update(deltaTime);


    // =====================================================
    // 3. ALTERNATOR
    // =====================================================

    alternator.update(
        deltaTime,
        engine.getTelemetry().rpm
    );


    // =====================================================
    // 4. STARTER
    // =====================================================

    bool startCommand = false;

    starter.update(
        deltaTime,
        battery.getTelemetry().batteryVoltage,
        startCommand,
        20.0
    );


    // =====================================================
    // 5. BATTERY
    // =====================================================

    battery.update(
        deltaTime,

        alternator
            .getTelemetry()
            .alternatorCurrent,

        starter
            .getTelemetry()
            .starterCurrent,

        0.0,

        20.0
    );


    // =====================================================
    // 6. CLUTCH
    // =====================================================

    clutch.update(
        deltaTime,

        0.0,

        engine
            .getTelemetry()
            .rpm,

        transmission
            .getTelemetry()
            .transmissionRpm,

        0.0,

        20.0
    );


    // =====================================================
    // 7. TRANSMISSION
    // =====================================================

    transmission.update(
        deltaTime,

        engine
            .getTelemetry()
            .rpm,

        clutch
            .getTelemetry()
            .transmittedTorque
    );


    // =====================================================
    // 8. BRAKE
    // =====================================================

    brake.update(
        deltaTime,

        1500.0,

        transmission
            .getTelemetry()
            .vehicleSpeed,

        0.0,

        20.0
    );
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