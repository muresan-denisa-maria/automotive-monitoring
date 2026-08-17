#include "FaultDetector.h"


FaultDetector::FaultDetector()
{
}


FaultDetectionResult FaultDetector::analyze(
    const TelemetryData& telemetry
) const
{
    FaultDetectionResult result;

    result.fault = DetectedFault::None;
    result.detected = false;
    result.severity = 0.0;


    // Verificarea supraincalzirii motorului
    if (telemetry.engine.engineTemperature > 110.0)
    {
        result.fault =
            DetectedFault::EngineOverheating;

        result.detected = true;

        result.severity =
            (telemetry.engine.engineTemperature - 110.0)
            / 30.0;
    }


    // Verificarea presiunii uleiului
    else if (telemetry.engine.oilPressure < 1.5)
    {
        result.fault =
            DetectedFault::LowOilPressure;

        result.detected = true;

        result.severity =
            (1.5 - telemetry.engine.oilPressure)
            / 1.5;
    }


    // Verificarea temperaturii lichidului de racire
    else if (telemetry.engine.coolantTemperature > 110.0)
    {
        result.fault =
            DetectedFault::EngineOverheating;

        result.detected = true;

        result.severity =
            (telemetry.engine.coolantTemperature - 110.0)
            / 30.0;
    }


    // Verificarea nivelului lichidului de racire
    else if (telemetry.engine.coolantLevel < 20.0)
    {
        result.fault =
            DetectedFault::LowCoolantLevel;

        result.detected = true;

        result.severity =
            (20.0 - telemetry.engine.coolantLevel)
            / 20.0;
    }


    // Verificarea bateriei
    else if (telemetry.battery.batteryVoltage < 11.5)
    {
        result.fault =
            DetectedFault::LowBatteryVoltage;

        result.detected = true;

        result.severity =
            (11.5 - telemetry.battery.batteryVoltage)
            / 2.0;
    }


    // Verificarea franelor
    else if (telemetry.brake.brakeDiscTemperature > 500.0)
    {
        result.fault =
            DetectedFault::BrakeOverheating;

        result.detected = true;

        result.severity =
            (telemetry.brake.brakeDiscTemperature - 500.0)
            / 300.0;
    }


    // Verificarea ambreiajului
    else if (telemetry.clutch.clutchSlip > 500.0)
    {
        result.fault =
            DetectedFault::ClutchSlip;

        result.detected = true;

        result.severity =
            (telemetry.clutch.clutchSlip - 500.0)
            / 2000.0;
    }


    // Verificarea temperaturii transmisiei
    else if (telemetry.transmission.transmissionTemperature > 120.0)
    {
        result.fault =
            DetectedFault::TransmissionOverheating;

        result.detected = true;

        result.severity =
            (telemetry.transmission.transmissionTemperature - 120.0)
            / 50.0;
    }


    if (result.severity > 1.0)
    {
        result.severity = 1.0;
    }

    return result;
}