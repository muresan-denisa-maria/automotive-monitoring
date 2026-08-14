#include "TelemetryData.h"
class Engine{
    private:
    EngineData engineData;

    public:
    Engine();

    void start();
    void stop();

EngineData getEngineData();
    void setEngineData( EngineData& data);
};