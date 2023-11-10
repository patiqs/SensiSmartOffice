#ifndef SHT4X_H
#define SHT4X_H

#include "sensor.h"

class Sht4xSensor : public Sensor
{
private:
    float ambientHumidity = 0.0f;
    float ambientTemperature = 0.0f;

    int64_t lastMeasurementTimeMs = 0;
    void startMeasurement();
    void pushRecords();

public:
    Sht4xSensor(const char *name, SensorContainer *parent) : Sensor(name, parent){};

    void begin();
    void read();
};

#endif /* SEN5X_H */
