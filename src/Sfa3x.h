#ifndef SFA3X_H
#define SFA3X_H

#include "sensor.h"

class Sfa3xSensor : public Sensor
{
private:
    void startMeasurement();

public:
    Sfa3xSensor(const char *name, SensorContainer *parent) : Sensor(name, parent){};

    void begin();
    void read();
};

#endif /* SFA3X_H */
