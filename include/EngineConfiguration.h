#ifndef ENGINE_CONFIGURATION_H
#define ENGINE_CONFIGURATION_H

struct EngineConfiguration
{
    double maxRpm;
    double idleRpm;

    double engineDisplacement;
    double oilCapacity;
    double coolantCapacity;

    double maximumTorque;
    double engineInertia;
    double frictionTorque;
    double starterTorque;
    double minimumCombustionRpm;

    double engineThermalCapacity;
    double oilThermalCapacity;
    double coolantThermalCapacity;

    double idleHeatPower;
    double maximumHeatPower;

    double engineToCoolantCoefficient;
    double engineToOilCoefficient;

    double oilCoolingCoefficient;
    double radiatorCoolingCoefficient;

    double minimumOilPressure;
    double maximumOilPressure;

    double coolantPumpRatio;
    double maximumCoolantFlowRate;

    double minimumCoolantPressure;
    double maximumCoolantPressure;

    double ambientPressure;
    double minimumManifoldPressure;

    double intakeHeatTransferFactor;
    double intakeResponseTime;

    double idleExhaustGasTemperature;
    double maximumExhaustGasTemperature;
    double exhaustResponseTime;

    double maximumExhaustBackpressure;

    double minimumExhaustOxygenPercentage;
    double maximumExhaustOxygenPercentage;
};

#endif