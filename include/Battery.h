#ifndef BATTERY_H
#define BATTERY_H

#include "TelemetryData.h"

struct BatteryConfiguration
{
    double nominalVoltage; //tensiunea nominala a bateriei
    double capacityAh; //capacitatea bateriei in Ah
    double internalResistance; //rezistenta interna a bateriei
    double maximumCurrent; //curentul maxim al bateriei
    double thermalCapacity; //capacitatea termica a bateriei
    double coolingCoefficient; //coeficientul de racire al bateriei
};

class Battery
{
public:
    Battery(
        const BatteryConfiguration& configuration,
        const BatteryData& initialData
    );

    void update(
        double deltaTime,
        double alternatorCurrent,//cat curent produce alternatorul
        double starterCurrent,//cat curent consuma electromotorul de pornire
        double electricalLoad,//cat consuma restul masinii, adica faruri, radio, etc
        double ambientTemperature//temperatura mediului
    );

    BatteryData getTelemetry() const;

private:
    BatteryConfiguration configuration;
    BatteryData data;
};

#endif