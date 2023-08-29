#ifndef SENSORCONTAINER_H
#define SENSORCONTAINER_H

#include "sensor.h"
#include <vector>

class SensorContainer
{
private:
    typedef void (*SensorCallback)(Sensor* sensor);
    std::vector<Sensor*> _sensors;

    template<typename _Function>
    void forEachSensors(_Function func);

public:
    std::vector<MeasureRecord> getMeasures();

    void begin();
    void read();
};

#endif /* SENSORCONTAINER_H */
