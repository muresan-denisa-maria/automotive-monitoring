#include <iostream>
#include "Vehicle.h"

int main()
{
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


    BatteryData batteryData{};

    batteryData.batteryVoltage = 12.6;
    batteryData.batteryCurrent = 0;
    batteryData.batteryTemperature = 20;
    batteryData.batteryStateOfCharge = 100;


    TransmissionData transmissionData{};

    transmissionData.transmissionTemperature = 20;
    transmissionData.transmissionFluidLevel = 100;
    transmissionData.transmissionFluidPressure = 0;
    transmissionData.transmissionGearPosition = 0;


    BrakeData brakeData{};

    brakeData.brakeFluidPressure = 0;
    brakeData.brakePadWear = 100;
    brakeData.brakeDiscTemperature = 20;


    Vehicle vehicle(
        engineConfiguration,
        engineData,
        batteryData,
        transmissionData,
        brakeData
    );


    vehicle.update(0.1);

    TelemetryData telemetry = vehicle.getTelemetry();


    std::cout << "RPM: " << telemetry.engine.rpm << std::endl;
    std::cout << "Engine temperature: "
              << telemetry.engine.engineTemperature
              << std::endl;

    std::cout << "Battery voltage: "
              << telemetry.battery.batteryVoltage
              << std::endl;

    std::cout << "Transmission temperature: "
              << telemetry.transmission.transmissionTemperature
              << std::endl;

    std::cout << "Brake disc temperature: "
              << telemetry.brake.brakeDiscTemperature
              << std::endl;

    return 0;
}