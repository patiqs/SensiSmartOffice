#ifndef SCD4X_H
#define SCD4X_H

#include "sensor.h"

class Scd4xSensor : public Sensor
{
private:
    uint16_t co2 = 0;
    float temperature = 0.0f;
    float humidity = 0.0f;
     int64_t lastMeasurementTimeMs = 0;
    void startMeasurement();
    void pushRecords();

public:
    Scd4xSensor(const char *name, SensorContainer *parent) : Sensor(name, parent){};

    void begin();
    void read();
};

#endif /* SCD4X_H */
