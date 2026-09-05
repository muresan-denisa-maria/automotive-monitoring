#include <iostream>

#include "Vehicle.h"
#include "FaultSimulator.h"


const char* faultTypeToString(
    FaultType type
)
{
    switch (type)
    {
    case FaultType::CoolingSystem:
        return "Cooling System";

    case FaultType::Alternator:
        return "Alternator";

    case FaultType::Brake:
        return "Brake";

    case FaultType::Battery:
        return "Battery";

    case FaultType::Engine:
        return "Engine";

    case FaultType::Clutch:
        return "Clutch";

    case FaultType::Transmission:
        return "Transmission";

    default:
        return "None";
    }
}


const char* detectedFaultTypeToString(
    DetectedFaultType type
)
{
    switch (type)
    {
    case DetectedFaultType::EngineOverheating:
        return "Engine Overheating";

    case DetectedFaultType::EnginePerformanceLoss:
        return "Engine Performance Loss";

    case DetectedFaultType::LowOilPressure:
        return "Low Oil Pressure";

    case DetectedFaultType::CoolingSystemFailure:
        return "Cooling System Failure";

    case DetectedFaultType::BatteryVoltageDrop:
        return "Battery Voltage Drop";

    case DetectedFaultType::LowAlternatorOutput:
        return "Low Alternator Output";

    case DetectedFaultType::BrakeFailure:
        return "Brake Failure";

    case DetectedFaultType::BrakeOverheating:
        return "Brake Overheating";

    case DetectedFaultType::ExcessiveClutchSlip:
        return "Excessive Clutch Slip";

    case DetectedFaultType::TransmissionPerformanceLoss:
        return "Transmission Performance Loss";

    case DetectedFaultType::TransmissionOverheating:
        return "Transmission Overheating";

    default:
        return "None";
    }
}

int main()
{
    EngineConfiguration engineConfiguration{};

    engineConfiguration.maxRpm = 6500;
    engineConfiguration.idleRpm = 800;

    engineConfiguration.engineDisplacement = 2.0;

    engineConfiguration.oilCapacity = 5.0;
    engineConfiguration.coolantCapacity = 7.0;

    engineConfiguration.maximumTorque = 220.0;
    engineConfiguration.engineInertia = 0.25;
    engineConfiguration.frictionTorque = 15.0;
    engineConfiguration.starterTorque = 50.0;
    engineConfiguration.minimumCombustionRpm = 200.0;

    engineConfiguration.engineThermalCapacity = 100000.0;
    engineConfiguration.oilThermalCapacity = 30000.0;
    engineConfiguration.coolantThermalCapacity = 30000.0;

    engineConfiguration.idleHeatPower = 12000.0;
    engineConfiguration.maximumHeatPower = 60000.0;

    engineConfiguration.engineToCoolantCoefficient = 500.0;
    engineConfiguration.engineToOilCoefficient = 150.0;

    engineConfiguration.oilCoolingCoefficient = 40.0;
    engineConfiguration.radiatorCoolingCoefficient = 700.0;

    engineConfiguration.minimumOilPressure = 1.5;
    engineConfiguration.maximumOilPressure = 4.5;

    engineConfiguration.coolantPumpRatio = 1.0;
    engineConfiguration.maximumCoolantFlowRate = 120.0;

    engineConfiguration.minimumCoolantPressure = 0.5;
    engineConfiguration.maximumCoolantPressure = 1.2;

    engineConfiguration.ambientPressure = 1.0;
    engineConfiguration.minimumManifoldPressure = 0.30;

    engineConfiguration.intakeHeatTransferFactor = 0.15;
    engineConfiguration.intakeResponseTime = 1.0;

    engineConfiguration.idleExhaustGasTemperature = 350.0;
    engineConfiguration.maximumExhaustGasTemperature = 900.0;
    engineConfiguration.exhaustResponseTime = 0.5;

    engineConfiguration.maximumExhaustBackpressure = 0.30;

    engineConfiguration.minimumExhaustOxygenPercentage = 0.5;
    engineConfiguration.maximumExhaustOxygenPercentage = 4.0;


    EngineData engineData{};

    engineData.rpm = 0;
    engineData.engineTemperature = 20;
    engineData.engineTorque = 0;

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


    TransmissionConfiguration transmissionConfiguration{};

    transmissionConfiguration.wheelRadius = 0.31;

    transmissionConfiguration.finalDriveRatio = 3.42;

    transmissionConfiguration.firstGearRatio = 3.80;
    transmissionConfiguration.secondGearRatio = 2.20;
    transmissionConfiguration.thirdGearRatio = 1.50;
    transmissionConfiguration.fourthGearRatio = 1.10;
    transmissionConfiguration.fifthGearRatio = 0.85;

    transmissionConfiguration.transmissionEfficiency = 0.92;

    transmissionConfiguration.thermalCapacity = 70000.0;
    transmissionConfiguration.coolingCoefficient = 80.0;
    transmissionConfiguration.ambientTemperature = 20.0;


    TransmissionData transmissionData{};

    transmissionData.transmissionTemperature = 20;
    transmissionData.transmissionFluidLevel = 100;
    transmissionData.transmissionFluidPressure = 0;

    transmissionData.transmissionGearPosition = 0;

    transmissionData.transmissionRpm = 0;
    transmissionData.wheelRpm = 0;
    transmissionData.vehicleSpeed = 0;


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
    brakeData.brakeForce = 0;


    AcceleratorConfiguration acceleratorConfiguration{};

    acceleratorConfiguration.maximumThrottle = 100;
    acceleratorConfiguration.throttleResponseTime = 0.2;


    AcceleratorData acceleratorData{};

    acceleratorData.throttlePosition = 0;


    ClutchConfiguration clutchConfiguration{};

    clutchConfiguration.maximumClutchTorque = 300;

    clutchConfiguration.clutchDiscMass = 5;
    clutchConfiguration.clutchDiscSpecificHeat = 500;

    clutchConfiguration.clutchEnergyFraction = 0.9;

    clutchConfiguration.coolingCoefficient = 10;

    clutchConfiguration.slipTorqueCoefficient = 1.0;


    ClutchData clutchData{};

    clutchData.clutchEngagement = 0;
    clutchData.transmittedTorque = 0;
    clutchData.clutchSlip = 0;
    clutchData.clutchDiscTemperature = 20;


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


    double deltaTime = 0.1;

    VehicleInput input{};


    for (int i = 0; i < 300; i++)
    {
        double time =
            i * deltaTime;


        input.startCommand = false;
        input.acceleratorInput = 0.0;
        input.brakeInput = 0.0;
        input.clutchInput = 0.0;
        input.gearPosition = 1;


        if (time < 0.6)
        {
            input.startCommand = true;
            input.acceleratorInput = 0.0;
            input.clutchInput = 100.0;
            input.gearPosition = 0;
        }

        else if (time < 1.5)
        {
            input.acceleratorInput = 0.0;
            input.clutchInput = 100.0;
            input.gearPosition = 0;
        }

        else if (time < 3.0)
        {
            input.acceleratorInput = 30.0;
            input.gearPosition = 1;

            input.clutchInput =
                100.0 -
                (
                    (time - 1.5) /
                    1.5
                ) *
                100.0;

            if (input.clutchInput < 0.0)
            {
                input.clutchInput = 0.0;
            }
        }

        else if (time < 7.0)
        {
            input.acceleratorInput = 40.0;
            input.clutchInput = 0.0;
            input.gearPosition = 1;
        }

        else if (time < 7.3)
        {
            input.acceleratorInput = 0.0;
            input.clutchInput = 100.0;
            input.gearPosition = 2;
        }

        else if (time < 8.0)
        {
            input.acceleratorInput = 30.0;
            input.gearPosition = 2;

            input.clutchInput =
                100.0 -
                (
                    (time - 7.3) /
                    0.7
                ) *
                100.0;

            if (input.clutchInput < 0.0)
            {
                input.clutchInput = 0.0;
            }
        }

        else if (time < 11.0)
        {
            input.acceleratorInput = 40.0;
            input.clutchInput = 0.0;
            input.gearPosition = 2;
        }

        else if (time < 11.3)
        {
            input.acceleratorInput = 0.0;
            input.clutchInput = 100.0;
            input.gearPosition = 3;
        }

        else if (time < 12.0)
        {
            input.acceleratorInput = 30.0;
            input.gearPosition = 3;

            input.clutchInput =
                100.0 -
                (
                    (time - 11.3) /
                    0.7
                ) *
                100.0;

            if (input.clutchInput < 0.0)
            {
                input.clutchInput = 0.0;
            }
        }

        else if (time < 15.0)
        {
            input.acceleratorInput = 40.0;
            input.clutchInput = 0.0;
            input.gearPosition = 3;
        }

        else if (time < 15.3)
        {
            input.acceleratorInput = 0.0;
            input.clutchInput = 100.0;
            input.gearPosition = 4;
        }

        else if (time < 16.0)
        {
            input.acceleratorInput = 30.0;
            input.gearPosition = 4;

            input.clutchInput =
                100.0 -
                (
                    (time - 15.3) /
                    0.7
                ) *
                100.0;

            if (input.clutchInput < 0.0)
            {
                input.clutchInput = 0.0;
            }
        }

        else if (time < 20.0)
        {
            input.acceleratorInput = 40.0;
            input.clutchInput = 0.0;
            input.gearPosition = 4;
        }

        else if (time < 20.3)
        {
            input.acceleratorInput = 0.0;
            input.clutchInput = 100.0;
            input.gearPosition = 5;
        }

        else if (time < 21.0)
        {
            input.acceleratorInput = 30.0;
            input.gearPosition = 5;

            input.clutchInput =
                100.0 -
                (
                    (time - 20.3) /
                    0.7
                ) *
                100.0;

            if (input.clutchInput < 0.0)
            {
                input.clutchInput = 0.0;
            }
        }

        else if (time < 24.0)
        {
            input.acceleratorInput = 40.0;
            input.clutchInput = 0.0;
            input.gearPosition = 5;
        }

        else
        {
            input.acceleratorInput = 0.0;
            input.brakeInput = 40.0;
            input.clutchInput = 100.0;
            input.gearPosition = 0;
        }


        vehicle.update(
            deltaTime,
            input
        );


        TelemetryData telemetry =
            vehicle.getTelemetry();


        FaultState fault =
            vehicle.getFaultState();


        DetectedFaultType detectedFault =
            vehicle.getDetectedFault();


        std::cout
            << "Time: "
            << time + deltaTime
            << " s"
            << " | RPM: "
            << telemetry.engine.rpm
            << " | Gear: "
            << telemetry.transmission.transmissionGearPosition
            << " | Clutch: "
            << telemetry.clutch.clutchEngagement
            << "%"
            << " | Brake: "
            << input.brakeInput
            << "%"
            << " | Speed: "
            << telemetry.transmission.vehicleSpeed * 3.6
            << " km/h"
            << " | Brake temp: "
            << telemetry.brake.brakeDiscTemperature
            << " C"
            << std::endl;


        if (fault.active &&
            i % 10 == 0)
        {
            std::cout
                << "FAULT -> "
                << faultTypeToString(
                    fault.type
                )
                << " | Severity: "
                << fault.severity * 100.0
                << "%"
                << std::endl;
        }


        if (detectedFault !=
                DetectedFaultType::None &&
            i % 10 == 0)
        {
            std::cout
                << "DETECTED -> "
                << detectedFaultTypeToString(
                    detectedFault
                )
                << std::endl;
        }
    }


    TelemetryData telemetry =
        vehicle.getTelemetry();


    FaultState finalFault =
        vehicle.getFaultState();


    DetectedFaultType finalDetectedFault =
        vehicle.getDetectedFault();


    std::cout
        << std::endl
        << "FINAL TELEMETRY"
        << std::endl;


    std::cout
        << "Battery temperature: "
        << telemetry.battery.batteryTemperature
        << " C"
        << std::endl;


    std::cout
        << "RPM: "
        << telemetry.engine.rpm
        << std::endl;


    std::cout
        << "Engine temperature: "
        << telemetry.engine.engineTemperature
        << " C"
        << std::endl;


    std::cout
        << "Oil temperature: "
        << telemetry.engine.oilTemperature
        << " C"
        << std::endl;


    std::cout
        << "Oil pressure: "
        << telemetry.engine.oilPressure
        << " bar"
        << std::endl;


    std::cout
        << "Coolant temperature: "
        << telemetry.engine.coolantTemperature
        << " C"
        << std::endl;


    std::cout
        << "Coolant pressure: "
        << telemetry.engine.coolantPressure
        << " bar"
        << std::endl;


    std::cout
        << "Coolant flow rate: "
        << telemetry.engine.coolantFlowRate
        << " L/min"
        << std::endl;


    std::cout
        << "Coolant pump speed: "
        << telemetry.engine.coolantPumpSpeed
        << " RPM"
        << std::endl;


    std::cout
        << "Intake air temperature: "
        << telemetry.engine.intakeAirTemperature
        << " C"
        << std::endl;


    std::cout
        << "Intake manifold pressure: "
        << telemetry.engine.intakeManifoldPressure
        << " bar"
        << std::endl;


    std::cout
        << "Exhaust gas temperature: "
        << telemetry.engine.exhaustGasTemperature
        << " C"
        << std::endl;


    std::cout
        << "Exhaust backpressure: "
        << telemetry.engine.exhaustBackpressure
        << " bar"
        << std::endl;


    std::cout
        << "Exhaust oxygen: "
        << telemetry.engine.exhaustOxygenPercentage
        << "%"
        << std::endl;


    std::cout
        << "Battery voltage: "
        << telemetry.battery.batteryVoltage
        << " V"
        << std::endl;


    std::cout
        << "Battery current: "
        << telemetry.battery.batteryCurrent
        << " A"
        << std::endl;


    std::cout
        << "Battery SOC: "
        << telemetry.battery.batteryStateOfCharge
        << "%"
        << std::endl;


    std::cout
        << "Alternator current: "
        << telemetry.alternator.alternatorCurrent
        << " A"
        << std::endl;


    std::cout
        << "Alternator voltage: "
        << telemetry.alternator.alternatorVoltage
        << " V"
        << std::endl;


    std::cout
        << "Starter current: "
        << telemetry.starter.starterCurrent
        << " A"
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
        << telemetry.transmission.vehicleSpeed * 3.6
        << " km/h"
        << std::endl;


    std::cout
        << "Transmission temperature: "
        << telemetry.transmission.transmissionTemperature
        << " C"
        << std::endl;


    std::cout
        << "Brake disc temperature: "
        << telemetry.brake.brakeDiscTemperature
        << " C"
        << std::endl;


    std::cout
        << "Brake force: "
        << telemetry.brake.brakeForce
        << " N"
        << std::endl;


    std::cout
        << "Brake fluid pressure: "
        << telemetry.brake.brakeFluidPressure
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
        << " C"
        << std::endl;


    std::cout
        << std::endl
        << "FINAL FAULT"
        << std::endl;


    std::cout
        << "Fault: "
        << faultTypeToString(
            finalFault.type
        )
        << std::endl;


    std::cout
        << "Active: "
        << (
            finalFault.active
                ? "Yes"
                : "No"
        )
        << std::endl;


    std::cout
        << "Severity: "
        << finalFault.severity * 100.0
        << "%"
        << std::endl;


    std::cout
        << std::endl
        << "FAULT DETECTOR"
        << std::endl;


    std::cout
        << "Detected: "
        << detectedFaultTypeToString(
            finalDetectedFault
        )
        << std::endl;


    return 0;
}