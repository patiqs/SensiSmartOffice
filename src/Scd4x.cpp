#include <SensirionI2CScd4x.h>
#include "Scd4x.h"

SensirionI2CScd4x scd4x;
static int measurementIntervalMs = 5100;

void Scd4xSensor::begin()
{
    scd4x.begin(Wire);
    startMeasurement();
    lastMeasurementTimeMs = millis();
    delay(measurementIntervalMs);
}

void Scd4xSensor::read()
{
    if (millis() - lastMeasurementTimeMs < measurementIntervalMs)
    {
        _parent->push(new InfoRecord(_name, "Waiting for next data"));
        pushRecords();
        return;
    };
    lastMeasurementTimeMs = millis();
    uint16_t error;

    error = scd4x.readMeasurement(co2, temperature, humidity);
    if (error)
    {
        HandleError("Error trying to execute readMeasurement(): ", error);
        error = scd4x.reinit();
        HandleError("Error trying to execute reInit(): ", error);
        startMeasurement();
        return;
    }
    if (co2 == 0 && humidity == 0 && temperature == 0)
    {
        startMeasurement();
        _parent->push(new ErrorRecord(_name, "Restarting"));
        return;
    }

    pushRecords();
}

void Scd4xSensor::pushRecords()
{
    _parent->push(new MeasureRecord(_name, SignalType::CO2_PARTS_PER_MILLION, co2 * 1.0F));
    _parent->push(new MeasureRecord(_name, SignalType::RELATIVE_HUMIDITY_PERCENTAGE, humidity));
    _parent->push(new MeasureRecord(_name, SignalType::TEMPERATURE_DEGREES_CELSIUS, temperature));
}

void Scd4xSensor::startMeasurement()
{
    uint16_t error;
    error = scd4x.startPeriodicMeasurement();
    HandleError("Error trying to execute startContinuousMeasurement(): ", error);
}
