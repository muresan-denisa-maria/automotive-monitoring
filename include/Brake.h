#ifndef BRAKE_H
#define BRAKE_H

#include "TelemetryData.h"

class Brake
{
public:
    Brake();

    void update(double deltaTime);

    BrakeData getTelemetry() const;

private:
    BrakeData data;
};

#endif