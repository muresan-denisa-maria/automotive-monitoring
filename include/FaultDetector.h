#ifndef FAULT_DETECTOR_H
#define FAULT_DETECTOR_H

#include "TelemetryData.h"

enum class DetectedFault
{
    None,
    EngineOverheating,
    LowOilPressure,
    LowBatteryVoltage,
    BrakeOverheating,
    ClutchSlip,
    LowCoolantLevel,
    TransmissionOverheating
};

struct FaultDetectionResult
{
    DetectedFault fault;
    bool detected;
    double severity;
};

class FaultDetector
{
public:
    FaultDetector();

    FaultDetectionResult analyze(
        const TelemetryData& telemetry
    ) const;
};

#endif