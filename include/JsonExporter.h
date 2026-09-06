#ifndef JSON_EXPORTER_H
#define JSON_EXPORTER_H

#include <string>

#include "TelemetryData.h"
#include "FaultDetector.h"


class JsonExporter
{
public:
    static std::string toJson(
        const TelemetryData& telemetry,
        DetectedFaultType detectedFault
    );

    static bool saveToFile(
        const std::string& fileName,
        const TelemetryData& telemetry,
        DetectedFaultType detectedFault
    );

private:
    static const char* detectedFaultToString(
        DetectedFaultType type
    );
};

#endif