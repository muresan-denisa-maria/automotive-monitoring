#ifndef VEHICLE_H
#define VEHICLE_H

#include "Engine.h"
#include "Battery.h"
#include "Transmission.h"
#include "Brake.h"
#include "TelemetryData.h"

class Vehicle
{
public:
    Vehicle();

    void update(double deltaTime);

    TelemetryData getTelemetry() const;

private:
    Engine engine;
    Battery battery;
    Transmission transmission;
    Brake brakes;
};

#endif