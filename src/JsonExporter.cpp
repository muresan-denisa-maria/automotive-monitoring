#include "JsonExporter.h"

#include <fstream>
#include <sstream>


const char* JsonExporter::detectedFaultToString(
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


std::string JsonExporter::toJson(
    const TelemetryData& telemetry,
    DetectedFaultType detectedFault
)
{
    std::ostringstream json;

    json
        << "{\n"

        << "  \"engine\": {\n"
        << "    \"rpm\": " << telemetry.engine.rpm << ",\n"
        << "    \"temperature\": " << telemetry.engine.engineTemperature << ",\n"
        << "    \"torque\": " << telemetry.engine.engineTorque << ",\n"
        << "    \"oilPressure\": " << telemetry.engine.oilPressure << ",\n"
        << "    \"oilTemperature\": " << telemetry.engine.oilTemperature << ",\n"
        << "    \"coolantTemperature\": " << telemetry.engine.coolantTemperature << ",\n"
        << "    \"coolantPressure\": " << telemetry.engine.coolantPressure << ",\n"
        << "    \"coolantFlowRate\": " << telemetry.engine.coolantFlowRate << "\n"
        << "  },\n"

        << "  \"battery\": {\n"
        << "    \"voltage\": " << telemetry.battery.batteryVoltage << ",\n"
        << "    \"current\": " << telemetry.battery.batteryCurrent << ",\n"
        << "    \"temperature\": " << telemetry.battery.batteryTemperature << ",\n"
        << "    \"stateOfCharge\": " << telemetry.battery.batteryStateOfCharge << "\n"
        << "  },\n"

        << "  \"alternator\": {\n"
        << "    \"voltage\": " << telemetry.alternator.alternatorVoltage << ",\n"
        << "    \"current\": " << telemetry.alternator.alternatorCurrent << ",\n"
        << "    \"temperature\": " << telemetry.alternator.alternatorTemperature << "\n"
        << "  },\n"

        << "  \"transmission\": {\n"
        << "    \"temperature\": " << telemetry.transmission.transmissionTemperature << ",\n"
        << "    \"gear\": " << telemetry.transmission.transmissionGearPosition << ",\n"
        << "    \"rpm\": " << telemetry.transmission.transmissionRpm << ",\n"
        << "    \"wheelRpm\": " << telemetry.transmission.wheelRpm << ",\n"
        << "    \"vehicleSpeed\": " << telemetry.transmission.vehicleSpeed * 3.6 << "\n"
        << "  },\n"

        << "  \"brake\": {\n"
        << "    \"fluidPressure\": " << telemetry.brake.brakeFluidPressure << ",\n"
        << "    \"padWear\": " << telemetry.brake.brakePadWear << ",\n"
        << "    \"discTemperature\": " << telemetry.brake.brakeDiscTemperature << ",\n"
        << "    \"force\": " << telemetry.brake.brakeForce << "\n"
        << "  },\n"

        << "  \"clutch\": {\n"
        << "    \"engagement\": " << telemetry.clutch.clutchEngagement << ",\n"
        << "    \"transmittedTorque\": " << telemetry.clutch.transmittedTorque << ",\n"
        << "    \"slip\": " << telemetry.clutch.clutchSlip << ",\n"
        << "    \"discTemperature\": " << telemetry.clutch.clutchDiscTemperature << "\n"
        << "  },\n"

        << "  \"fault\": {\n"
        << "    \"detected\": \""
        << detectedFaultToString(detectedFault)
        << "\"\n"
        << "  }\n"

        << "}";

    return json.str();
}


bool JsonExporter::saveToFile(
    const std::string& fileName,
    const TelemetryData& telemetry,
    DetectedFaultType detectedFault
)
{
    std::ofstream file(fileName);

    if (!file.is_open())
    {
        return false;
    }

    file << toJson(
        telemetry,
        detectedFault
    );

    file.close();

    return true;
}