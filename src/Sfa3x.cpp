#include <SensirionI2CSfa3x.h>
#include "Sfa3x.h"

SensirionI2CSfa3x sfa3x;

void Sfa3xSensor::begin()
{
    sfa3x.begin(Wire);
    startMeasurement();
}

void Sfa3xSensor::read()
{
    uint16_t error;
    int16_t hcho;
    int16_t humidity;
    int16_t temperature;

    error = sfa3x.readMeasuredValues(hcho, humidity, temperature);

    // if (error)
    // {
    //     HandleError("Error trying to execute readMeasuredValues(): ", error);
    //     return;
    // }

    // if (hcho == 0 && humidity == 0 && temperature == 0)
    // {
    //     startMeasurement();
    //     _parent->push(new ErrorRecord(_name, "Restarting"));
    //     return;
    // }

    _parent->push(new MeasureRecord(_name, SignalType::HCHO_PARTS_PER_BILLION, hcho / 5.0F));
    _parent->push(new MeasureRecord(_name, SignalType::RELATIVE_HUMIDITY_PERCENTAGE, humidity / 100.0F));
    _parent->push(new MeasureRecord(_name, SignalType::TEMPERATURE_DEGREES_CELSIUS, temperature / 200.0F));
}

void Sfa3xSensor::startMeasurement()
{
    uint16_t error;
    error = sfa3x.startContinuousMeasurement();

    HandleError("Error trying to execute startContinuousMeasurement(): ", error);
}
