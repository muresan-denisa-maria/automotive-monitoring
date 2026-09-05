#include "FaultDetector.h"

#include <cmath>


FaultDetector::FaultDetector()
{
    previousVehicleSpeed =
        0.0;

    previousVehicleSpeedInitialized =
        false;

    clutchSlipDuration =
        0.0;

    transmissionLossDuration =
        0.0;

    enginePerformanceLossDuration =
        0.0;
}


DetectedFaultType FaultDetector::detect(
    const TelemetryData& telemetry,
    double deltaTime,
    double acceleratorInput,
    double brakeInput,
    double vehicleMass
)
{
    double currentVehicleSpeed =
        telemetry.transmission.vehicleSpeed;


    double vehicleAcceleration =
        0.0;


    if (previousVehicleSpeedInitialized &&
        deltaTime > 0.0)
    {
        vehicleAcceleration =
            (
                currentVehicleSpeed -
                previousVehicleSpeed
            ) /
            deltaTime;
    }


    previousVehicleSpeed =
        currentVehicleSpeed;

    previousVehicleSpeedInitialized =
        true;


    if (telemetry.engine.engineTemperature >
        110.0)
    {
        return DetectedFaultType::EngineOverheating;
    }


    if (telemetry.engine.rpm > 600.0 &&
        telemetry.engine.oilPressure < 1.2)
    {
        return DetectedFaultType::LowOilPressure;
    }


    if (telemetry.engine.rpm > 600.0 &&
        telemetry.engine.coolantFlowRate < 8.0)
    {
        return DetectedFaultType::CoolingSystemFailure;
    }


    if (telemetry.battery.batteryCurrent > 15.0 &&
        telemetry.battery.batteryVoltage < 12.35)
    {
        return DetectedFaultType::BatteryVoltageDrop;
    }


    if (telemetry.engine.rpm > 700.0)
    {
        double minimumExpectedAlternatorCurrent =
            0.012 *
            telemetry.engine.rpm;


        if (telemetry.alternator.alternatorCurrent <
            minimumExpectedAlternatorCurrent)
        {
            return DetectedFaultType::LowAlternatorOutput;
        }
    }


    if (brakeInput >= 20.0)
    {
        double minimumExpectedBrakePressure =
            brakeInput *
            0.75;


        if (telemetry.brake.brakeFluidPressure <
            minimumExpectedBrakePressure)
        {
            return DetectedFaultType::BrakeFailure;
        }
    }


    if (telemetry.brake.brakeDiscTemperature >
        500.0)
    {
        return DetectedFaultType::BrakeOverheating;
    }


    bool enginePerformanceTestActive =
        acceleratorInput >= 30.0 &&
        telemetry.engine.rpm > 900.0 &&
        telemetry.transmission.transmissionGearPosition > 0 &&
        telemetry.clutch.clutchEngagement > 90.0;


    if (enginePerformanceTestActive)
    {
        double minimumExpectedTorque =
            telemetry.engine.throttlePosition *
            1.3;


        if (telemetry.engine.engineTorque <
            minimumExpectedTorque)
        {
            enginePerformanceLossDuration +=
                deltaTime;
        }
        else
        {
            enginePerformanceLossDuration =
                0.0;
        }
    }
    else
    {
        enginePerformanceLossDuration =
            0.0;
    }


    bool transmissionTestActive =
        telemetry.transmission.transmissionGearPosition > 0 &&
        telemetry.clutch.clutchEngagement > 95.0 &&
        brakeInput < 5.0 &&
        currentVehicleSpeed > 2.0 &&
        std::abs(
            telemetry.clutch.transmittedTorque
        ) > 20.0 &&
        std::abs(
            telemetry.transmission.transmissionRpm
        ) > 100.0;


    if (transmissionTestActive &&
        previousVehicleSpeedInitialized)
    {
        double transmissionAngularVelocity =
            std::abs(
                telemetry.transmission.transmissionRpm
            ) *
            2.0 *
            3.14159265359 /
            60.0;


        double inputPower =
            std::abs(
                telemetry.clutch.transmittedTorque
            ) *
            transmissionAngularVelocity;


        double outputPower =
            vehicleMass *
            vehicleAcceleration *
            currentVehicleSpeed;


        if (outputPower < 0.0)
        {
            outputPower =
                0.0;
        }


        if (inputPower > 100.0)
        {
            double estimatedEfficiency =
                outputPower /
                inputPower;


            if (estimatedEfficiency < 0.78)
            {
                transmissionLossDuration +=
                    deltaTime;
            }
            else
            {
                transmissionLossDuration =
                    0.0;
            }
        }
        else
        {
            transmissionLossDuration =
                0.0;
        }
    }
    else
    {
        transmissionLossDuration =
            0.0;
    }


    bool clutchTestActive =
        telemetry.transmission.transmissionGearPosition > 0 &&
        telemetry.clutch.clutchEngagement > 90.0 &&
        acceleratorInput > 20.0 &&
        telemetry.engine.rpm > 800.0;


    if (clutchTestActive)
    {
        double clutchSlip =
            std::abs(
                telemetry.clutch.clutchSlip
            );


        if (clutchSlip > 500.0)
        {
            clutchSlipDuration +=
                deltaTime;
        }
        else
        {
            clutchSlipDuration =
                0.0;
        }
    }
    else
    {
        clutchSlipDuration =
            0.0;
    }


    if (transmissionLossDuration >=
        1.0)
    {
        return
            DetectedFaultType::TransmissionPerformanceLoss;
    }


    if (enginePerformanceLossDuration >=
        1.0)
    {
        return
            DetectedFaultType::EnginePerformanceLoss;
    }


    if (clutchSlipDuration >=
        1.0)
    {
        return
            DetectedFaultType::ExcessiveClutchSlip;
    }


    if (telemetry.transmission.transmissionTemperature >
        120.0)
    {
        return
            DetectedFaultType::TransmissionOverheating;
    }


    return DetectedFaultType::None;
}