#ifndef TELEMETRY_DATA_H
#define TELEMETRY_DATA_H

struct EngineData {
        //pentru Engine
    double rpm;//revolutions per minute
    double engineTemperature;//temperatura motorului

        //pentru Oil system
    double oilPressure;//presiunea uleiului
    double oilTemperature;//temperatura uleiului

        //pentru Cooling system
    double coolantTemperature;//temperatura lichidului de racire din sistemul de racire al motorului
    double coolantPressure;//presiunea lichidului de racire din sistemul de racire al motorului
    double coolantLevel; //nivelul lichidului de racire din sistemul de racire al motorului
    double coolantFlowRate; //rata de flux a lichidului de racire din sistemul de racire al motorului
    double coolantPumpSpeed; //viteza pompei de lichid de racire din sistemul de racire al motorului

        //pentru Intake system
    double intakeAirTemperature; //temperatura aerului de admisie/care intra in motor  
    double throttlePosition;//pozitia clapetei de acceleratie
    //adica cat ii de deschisa clapeta de acceleratie, exprimata in procente
    double intakeManifoldPressure; //presiunea din galeria de admisie

        //pentru Exhaust system
    double exhaustGasTemperature; //temperatura gazelor de evacuare
    double exhaustBackpressure; //presiunea de rezistență în sistemul de evacuare
    double exhaustOxygenPercentage; //procentul de oxigen din gazele de evacuare
};

struct TransmissionData {
        //pentru Transmission
    double transmissionTemperature; //temperatura transmisiei
    double transmissionFluidLevel; //nivelul lichidului de transmisie
    double transmissionFluidPressure; //presiunea lichidului de transmisie
    double transmissionGearPosition; //pozitia treptei de viteza a transmisiei
};

struct BatteryData {
        //pentru Battery
    double batteryVoltage; //tensiunea bateriei
    double batteryCurrent; //curentul bateriei
    double batteryTemperature; //temperatura bateriei
    double batteryStateOfCharge; //starea de incarcare a bateriei
};
struct AlternatorData {
        //pentru Alternator
    double alternatorVoltage;
    double alternatorCurrent;
    double alternatorTemperature;
};
struct StarterData {
        //pentru Starter
    double starterCurrent; //curentul consumat de starter
    double starterVoltage; //tensiunea starterului
    double starterTemperature; //temperatura starterului
};

struct BrakeData {
        //pentru Brake
    double brakeFluidPressure; //presiunea lichidului de frana
    double brakePadWear; //uzura placutelor de frana
    double brakeDiscTemperature; //temperatura discurilor de frana
};
struct AcceleratorData {
        //pentru Accelerator
    double throttlePosition; //pozitia clapetei de acceleratie
};
struct ClutchData {
        //pentru Clutch
    double clutchEngagement; //gradul de cuplare al ambreiajului in procente
    double transmittedTorque; //cuplul transmis prin ambreiaj
    double clutchSlip; //diferenta de turatie dintre motor si transmisie
    double clutchDiscTemperature; //temperatura discului de ambreiaj
};
struct TelemetryData
{
    EngineData engine;
    TransmissionData transmission;
    BatteryData battery;
    BrakeData brake;
    AlternatorData alternator;
    StarterData starter;
    ClutchData clutch;

};

#endif 