#ifndef SEN5X_H
#define SEN5X_H

#include "sensor.h"

class Sen5xSensor : public Sensor
{
private:
    float massConcentrationPm1p0 = 0.0f;
    float massConcentrationPm2p5 = 0.0f;
    float massConcentrationPm4p0 = 0.0f;
    float massConcentrationPm10p0 = 0.0f;
    float ambientHumidity = 0.0f;
    float ambientTemperature = 0.0f;
    float vocIndex = 0.0f;
    float noxIndex = 0.0f;

    int64_t lastMeasurementTimeMs = 0;
    void startMeasurement();
    void pushRecords();

public:
    Sen5xSensor(const char *name, SensorContainer *parent) : Sensor(name, parent){};

    void begin();
    void read();
};

#endif /* SEN5X_H */
