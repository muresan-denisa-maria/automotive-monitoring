#ifndef FAULT_DETECTOR_H
#define FAULT_DETECTOR_H

#include "TelemetryData.h"


enum class DetectedFaultType
{
    None,

    EngineOverheating,
    EnginePerformanceLoss,

    LowOilPressure,

    CoolingSystemFailure,

    BatteryVoltageDrop,
    LowAlternatorOutput,

    BrakeFailure,
    BrakeOverheating,

    ExcessiveClutchSlip,

    TransmissionPerformanceLoss,
    TransmissionOverheating
};


class FaultDetector
{
public:
    FaultDetector();

    DetectedFaultType detect(
        const TelemetryData& telemetry,
        double deltaTime,
        double acceleratorInput,
        double brakeInput,
        double vehicleMass
    );

private:
    double previousVehicleSpeed;

    bool previousVehicleSpeedInitialized;

    double clutchSlipDuration;

    double transmissionLossDuration;

    double enginePerformanceLossDuration;
};

#endif