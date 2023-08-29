#include "sensorContainer.h"
#include "Sfa3x.h"
#include <algorithm>
#include <Wire.h>
#include <Arduino.h>

#define I2C_SDA 33
#define I2C_SCL 32

void SensorContainer::begin()
{
    Wire.begin(I2C_SDA, I2C_SCL, 10000UL);

    _sensors.push_back(new Sfa3xSensor("Sfa3x"));
    _sensors.push_back(new Sfa3xSensor("Sfa3x2"));

    forEachSensors([](Sensor *sensor)
                   { sensor->begin(); });
}

void SensorContainer::read()
{
    forEachSensors([](Sensor *sensor)
                   { sensor->read(); });
}

std::vector<MeasureRecord> SensorContainer::getMeasures()
{
    std::vector<MeasureRecord> measures;

    forEachSensors([&](Sensor *sensor)
                   {
            std::vector<MeasureRecord> sm = sensor->getMeasures();
        measures.insert(measures.end(), sm.begin(), sm.end()); });

    return measures;
}

void AddMeasure(std::vector<MeasureRecord> measures) {}

template <typename _Function>
void SensorContainer::forEachSensors(_Function func)
{
    std::for_each(_sensors.begin(), _sensors.end(), func);
}
