#ifndef SFA3X_H
#define SFA3X_H

#include "sensor.h"

class Sfa3xSensor : public Sensor
{
private:
    void SetError(String prefix, uint16_t error);
    void startMeasurement();

public:
    Sfa3xSensor(const char *name) : Sensor(name){};

    std::vector<MeasureRecord> getMeasures() { return _measures; };

    void begin();
    void read();
};

#endif /* SFA3X_H */
