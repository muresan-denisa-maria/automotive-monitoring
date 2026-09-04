#ifndef TELEMETRY_DATA_H
#define TELEMETRY_DATA_H

struct EngineData
{
    // Engine
    double rpm;
    double engineTemperature;
    double engineTorque;

    // Oil system
    double oilPressure;
    double oilTemperature;

    // Cooling system
    double coolantTemperature;
    double coolantPressure;
    double coolantLevel;
    double coolantFlowRate;
    double coolantPumpSpeed;

    // Intake system
    double intakeAirTemperature;
    double throttlePosition;
    double intakeManifoldPressure;

    // Exhaust system
    double exhaustGasTemperature;
    double exhaustBackpressure;
    double exhaustOxygenPercentage;
};

struct TransmissionData
{
    // Transmission
    double transmissionTemperature;
    double transmissionFluidLevel;
    double transmissionFluidPressure;
    double transmissionGearPosition;

    // Rotational and vehicle data
    double transmissionRpm;
    double wheelRpm;
    double vehicleSpeed;
};

struct BatteryData
{
    // Battery
    double batteryVoltage;
    double batteryCurrent;
    double batteryTemperature;
    double batteryStateOfCharge;
};

struct AlternatorData
{
    // Alternator
    double alternatorVoltage;
    double alternatorCurrent;
    double alternatorTemperature;
};

struct StarterData
{
    // Starter
    double starterCurrent;
    double starterVoltage;
    double starterTemperature;
};

struct BrakeData
{
    // Brake
    double brakeFluidPressure;
    double brakePadWear;
    double brakeDiscTemperature;
    double brakeForce;
};

struct AcceleratorData
{
    // Accelerator
    double throttlePosition;
};

struct ClutchData
{
    // Clutch
    double clutchEngagement;
    double transmittedTorque;
    double clutchSlip;
    double clutchDiscTemperature;
};

struct TelemetryData
{
    EngineData engine;
    TransmissionData transmission;
    BatteryData battery;
    AlternatorData alternator;
    StarterData starter;
    BrakeData brake;
    AcceleratorData accelerator;
    ClutchData clutch;
};

#endif