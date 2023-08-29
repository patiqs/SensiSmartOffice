#ifndef SENSOR_H
#define SENSOR_H

#include "measureRecord.h"
#include <vector>

class Sensor
{
private:
    Sensor() {}

protected:
    Sensor(const char *name) { _name = name; }
    String _name;
    std::vector<MeasureRecord> _measures;

public:
    std::vector<MeasureRecord> getMeasures() { return _measures; };

    virtual void begin() = 0;
    virtual void read() = 0;
};

#endif /* SENSOR_H */
