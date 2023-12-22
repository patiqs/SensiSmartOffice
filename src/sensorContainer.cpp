#include "sensorContainer.h"

#ifdef enableSen5x
    #include "Sen5x.h"
#endif

#ifdef enableScd4x
    #include "Scd4x.h"
#endif

#ifdef enableSht4x
    #include "Sht4x.h"
#endif

#ifdef enableSfa3x
    #include "Sfa3x.h"
#endif

#ifdef enableSacs3
//    #include "Sacs3.h"
#endif


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


    
    #ifdef enableSen5x
    _sensors.push_back(new Sen5xSensor("Sen5x", this));
    #endif

    #ifdef enableScd4x
    _sensors.push_back(new Scd4xSensor("Scd4x", this)); 
    #endif

    #ifdef enableSht4x
    _sensors.push_back(new Sht4xSensor("Sht4x", this));
    #endif

    #ifdef enableSfa3x
    _sensors.push_back(new Sfa3xSensor("Sfa3x", this));
    #endif

    #ifdef enableSacs3
    _sensors.push_back(new Sacs3Sensor("Sacs3", this));
    #endif
    

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
