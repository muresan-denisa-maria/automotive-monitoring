#include <iostream>

#include "Vehicle.h"


int main()
{
    // =====================================================
    // ENGINE
    // =====================================================

    EngineConfiguration engineConfiguration{};

    engineConfiguration.maxRpm = 6500;
    engineConfiguration.engineDisplacement = 2.0;
    engineConfiguration.oilCapacity = 5.0;
    engineConfiguration.coolantCapacity = 7.0;


    EngineData engineData{};

    engineData.rpm = 0;
    engineData.engineTemperature = 20;

    engineData.oilPressure = 0;
    engineData.oilTemperature = 20;

    engineData.coolantTemperature = 20;
    engineData.coolantPressure = 0;
    engineData.coolantLevel = 100;
    engineData.coolantFlowRate = 0;
    engineData.coolantPumpSpeed = 0;

    engineData.intakeAirTemperature = 20;
    engineData.throttlePosition = 0;
    engineData.intakeManifoldPressure = 1;

    engineData.exhaustGasTemperature = 20;
    engineData.exhaustBackpressure = 0;
    engineData.exhaustOxygenPercentage = 21;


    // =====================================================
    // BATTERY
    // =====================================================

    BatteryConfiguration batteryConfiguration{};

    batteryConfiguration.nominalVoltage = 12.6;
    batteryConfiguration.capacityAh = 60;
    batteryConfiguration.internalResistance = 0.005;
    batteryConfiguration.maximumCurrent = 500;
    batteryConfiguration.thermalCapacity = 50000;
    batteryConfiguration.coolingCoefficient = 10;


    BatteryData batteryData{};

    batteryData.batteryVoltage = 12.6;
    batteryData.batteryCurrent = 0;
    batteryData.batteryTemperature = 20;
    batteryData.batteryStateOfCharge = 100;


    // =====================================================
    // ALTERNATOR
    // =====================================================

    AlternatorConfiguration alternatorConfiguration{};

    alternatorConfiguration.maximumCurrent = 120;
    alternatorConfiguration.maximumRpm = 6000;
    alternatorConfiguration.nominalVoltage = 14.2;
    alternatorConfiguration.efficiency = 0.7;
    alternatorConfiguration.thermalCapacity = 5000;
    alternatorConfiguration.coolingCoefficient = 10;
    alternatorConfiguration.ambientTemperature = 20;


    AlternatorData alternatorData{};

    alternatorData.alternatorVoltage = 14.2;
    alternatorData.alternatorCurrent = 0;
    alternatorData.alternatorTemperature = 20;


    // =====================================================
    // STARTER
    // =====================================================

    StarterConfiguration starterConfiguration{};

    starterConfiguration.maximumCurrent = 250;
    starterConfiguration.minimumVoltage = 10.0;
    starterConfiguration.efficiency = 0.8;
    starterConfiguration.thermalCapacity = 3000;
    starterConfiguration.coolingCoefficient = 10;


    StarterData starterData{};

    starterData.starterCurrent = 0;
    starterData.starterVoltage = 0;
    starterData.starterTemperature = 20;


    // =====================================================
    // TRANSMISSION
    // =====================================================

    TransmissionConfiguration transmissionConfiguration{};

    transmissionConfiguration.wheelRadius = 0.31;

    transmissionConfiguration.finalDriveRatio = 3.42;

    transmissionConfiguration.firstGearRatio = 3.80;
    transmissionConfiguration.secondGearRatio = 2.20;
    transmissionConfiguration.thirdGearRatio = 1.50;
    transmissionConfiguration.fourthGearRatio = 1.10;
    transmissionConfiguration.fifthGearRatio = 0.85;

    transmissionConfiguration.transmissionEfficiency = 0.92;


    TransmissionData transmissionData{};

    transmissionData.transmissionTemperature = 20;
    transmissionData.transmissionFluidLevel = 100;
    transmissionData.transmissionFluidPressure = 0;

    // 0 = neutral
    transmissionData.transmissionGearPosition = 0;

    transmissionData.transmissionRpm = 0;
    transmissionData.wheelRpm = 0;
    transmissionData.vehicleSpeed = 0;


    // =====================================================
    // BRAKE
    // =====================================================

    BrakeConfiguration brakeConfiguration{};

    brakeConfiguration.maximumBrakeForce = 12000;

    brakeConfiguration.brakeDiscMass = 8;
    brakeConfiguration.brakeDiscSpecificHeat = 460;
    brakeConfiguration.brakeDiscArea = 0.2;

    brakeConfiguration.brakeEnergyFraction = 0.9;

    brakeConfiguration.coolingCoefficient = 50;

    brakeConfiguration.brakePadWearCoefficient = 0.000001;

    brakeConfiguration.maximumBrakePressure = 100;


    BrakeData brakeData{};

    brakeData.brakeFluidPressure = 0;
    brakeData.brakePadWear = 100;
    brakeData.brakeDiscTemperature = 20;


    // =====================================================
    // ACCELERATOR
    // =====================================================

    AcceleratorConfiguration acceleratorConfiguration{};

    acceleratorConfiguration.maximumThrottle = 100;
    acceleratorConfiguration.throttleResponseTime = 0.2;


    AcceleratorData acceleratorData{};

    acceleratorData.throttlePosition = 0;


    // =====================================================
    // CLUTCH
    // =====================================================

    ClutchConfiguration clutchConfiguration{};

    clutchConfiguration.maximumClutchTorque = 300;

    clutchConfiguration.clutchDiscMass = 5;
    clutchConfiguration.clutchDiscSpecificHeat = 500;

    clutchConfiguration.clutchEnergyFraction = 0.9;

    clutchConfiguration.coolingCoefficient = 10;


    ClutchData clutchData{};

    clutchData.clutchEngagement = 0;
    clutchData.transmittedTorque = 0;
    clutchData.clutchSlip = 0;
    clutchData.clutchDiscTemperature = 20;


    // =====================================================
    // VEHICLE
    // =====================================================

    Vehicle vehicle(
        engineConfiguration,
        engineData,

        batteryConfiguration,
        batteryData,

        alternatorConfiguration,
        alternatorData,

        starterConfiguration,
        starterData,

        transmissionConfiguration,
        transmissionData,

        brakeConfiguration,
        brakeData,

        acceleratorConfiguration,
        acceleratorData,

        clutchConfiguration,
        clutchData
    );


    // =====================================================
    // SIMULATION
    // =====================================================

    vehicle.update(0.1);


    // =====================================================
    // TELEMETRY
    // =====================================================

    TelemetryData telemetry =
        vehicle.getTelemetry();


    std::cout
        << "RPM: "
        << telemetry.engine.rpm
        << std::endl;


    std::cout
        << "Engine temperature: "
        << telemetry.engine.engineTemperature
        << std::endl;


    std::cout
        << "Battery voltage: "
        << telemetry.battery.batteryVoltage
        << std::endl;


    std::cout
        << "Battery current: "
        << telemetry.battery.batteryCurrent
        << std::endl;


    std::cout
        << "Battery SOC: "
        << telemetry.battery.batteryStateOfCharge
        << "%"
        << std::endl;


    std::cout
        << "Alternator current: "
        << telemetry.alternator.alternatorCurrent
        << std::endl;


    std::cout
        << "Starter current: "
        << telemetry.starter.starterCurrent
        << std::endl;


    std::cout
        << "Transmission RPM: "
        << telemetry.transmission.transmissionRpm
        << std::endl;


    std::cout
        << "Wheel RPM: "
        << telemetry.transmission.wheelRpm
        << std::endl;


    std::cout
        << "Vehicle speed: "
        << telemetry.transmission.vehicleSpeed
        << " km/h"
        << std::endl;


    std::cout
        << "Transmission temperature: "
        << telemetry.transmission.transmissionTemperature
        << std::endl;


    std::cout
        << "Brake disc temperature: "
        << telemetry.brake.brakeDiscTemperature
        << std::endl;


    std::cout
        << "Accelerator position: "
        << telemetry.accelerator.throttlePosition
        << "%"
        << std::endl;


    std::cout
        << "Clutch engagement: "
        << telemetry.clutch.clutchEngagement
        << "%"
        << std::endl;


    std::cout
        << "Clutch transmitted torque: "
        << telemetry.clutch.transmittedTorque
        << " Nm"
        << std::endl;


    std::cout
        << "Clutch slip: "
        << telemetry.clutch.clutchSlip
        << " RPM"
        << std::endl;


    std::cout
        << "Clutch disc temperature: "
        << telemetry.clutch.clutchDiscTemperature
        << std::endl;


    return 0;
}