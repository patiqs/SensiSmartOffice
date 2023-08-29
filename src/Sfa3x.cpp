#include "main.h"
#include <SensirionI2CSfa3x.h>
#include "Sfa3x.h"

SensirionI2CSfa3x sfa3x;

void Sfa3xSensor::begin()
{
    Serial.println("@08291430");
    sfa3x.begin(Wire);

    startMeasurement();
}

void Sfa3xSensor::read()
{
    uint16_t error;
    int16_t hcho;
    int16_t humidity;
    int16_t temperature;

    _measures.clear();
    error = sfa3x.readMeasuredValues(hcho, humidity, temperature);

    if (error)
    {
        SetError("Error trying to execute readMeasuredValues(): ", error);
        return;
    }

    if (hcho == 0 && humidity == 0 && temperature == 0)
    {
        startMeasurement();
        _measures.push_back({_name, SignalType::UNDEFINED, 0.0F, "Restarting", ""});
        return;
    }

    _measures.push_back({_name, SignalType::HCHO_PARTS_PER_BILLION, hcho / 5.0F, "", "ppb"});
    _measures.push_back({_name, SignalType::RELATIVE_HUMIDITY_PERCENTAGE, humidity / 100.0F, "", "% RH"});
    _measures.push_back({_name, SignalType::TEMPERATURE_DEGREES_CELSIUS, temperature / 200.0F, "", "Celsius"});
}

void Sfa3xSensor::startMeasurement()
{
    uint16_t error;
    error = sfa3x.startContinuousMeasurement();
    if (error)
        SetError("Error trying to execute startContinuousMeasurement(): ", error);
}

void Sfa3xSensor::SetError(String prefix, uint16_t error)
{

    char buffer[256];
    errorToString(error, buffer, sizeof(buffer));
    _measures.push_back({_name, SignalType::UNDEFINED, 0.0F, prefix, buffer});
}
