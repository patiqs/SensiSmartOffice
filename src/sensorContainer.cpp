#include "sensorContainer.h"
#include "Sfa3x.h"
#include "Scd4x.h"
#include "Sen5x.h"
#include <algorithm>
#include <Wire.h>
#include <Arduino.h>

#define I2C_SDA 33
#define I2C_SCL 32

void SensorContainer::begin()
{
    pinMode(I2C_SDA, OUTPUT | PULLUP);
    pinMode(I2C_SCL, OUTPUT | PULLUP);

    Wire.begin(I2C_SDA, I2C_SCL, 10000UL);

    _sensors.push_back(new Scd4xSensor("Scd4x", this));
    _sensors.push_back(new Sfa3xSensor("Sfa3x", this));
    _sensors.push_back(new Sen5xSensor("Sen5x", this));
    _sensors.push_back(new SACS3Sensor("Sacs3", this));
)

    forEachSensors([](Sensor *sensor)
                   {sensor->begin();
                   delay(500); });
}

void SensorContainer::read()
{
    forEachSensors([](Sensor *sensor)
                   { sensor->read(); });
}

void SensorContainer::accept(uiInterface *ui)
{
    while (!_records.empty())
    {
        Record *record = _records.front();
        Serial.println(record->toString());
        record->accept(ui);
        _records.pop();
        delete record;
    }
}

template <typename _Function>
void SensorContainer::forEachSensors(_Function func)
{
    std::for_each(_sensors.begin(), _sensors.end(), func);
}
