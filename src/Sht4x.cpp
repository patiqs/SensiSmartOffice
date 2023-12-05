#include <SensirionI2CSht4x.h>
#include "Sht4x.h"

#define SHT4x_I2C_ADDR 0x44
SensirionI2CSht4x Sht4x;
static int measurementIntervalMs = 5100;

void Sht4xSensor::begin()
{
    Sht4x.begin(Wire, SHT4x_I2C_ADDR);
    startMeasurement();
    // lastMeasurementTimeMs = millis();
    // delay(measurementIntervalMs);
}

void Sht4xSensor::read()
{
    if (millis() - lastMeasurementTimeMs < measurementIntervalMs)
    {
        _parent->push(new InfoRecord(_name, "Waiting for next data"));
        pushRecords();
        return;
    };
    lastMeasurementTimeMs = millis();
    uint16_t error;

    error = Sht4x.measureLowestPrecision(ambientTemperature, ambientHumidity);
    if (error)
    {
        HandleError("Error trying to execute readMeasuredValues(): ", error);
        error = Sht4x.softReset();
        HandleError("Error trying to execute deviceReset(): ", error);
        startMeasurement();
        return;
    }
    if (ambientHumidity == 0 && ambientTemperature == 0)
    {
        startMeasurement();
        _parent->push(new ErrorRecord(_name, "Restarting"));
        return;
    }

    pushRecords();
}

void Sht4xSensor::pushRecords()
{
    _parent->push(new MeasureRecord(_name, SignalType::RELATIVE_HUMIDITY_PERCENTAGE, ambientHumidity));
    _parent->push(new MeasureRecord(_name, SignalType::TEMPERATURE_DEGREES_CELSIUS, ambientTemperature));
}

void Sht4xSensor::startMeasurement()
{
    // uint16_t error;
    // error = Sht4x.startMeasurement();
    // HandleError("Error trying to execute startContinuousMeasurement(): ", error);
}
