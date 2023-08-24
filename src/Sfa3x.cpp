#include "main.h"
#include <SensirionI2CSfa3x.h>
#include "Sfa3x.h"

#define I2C_SDA 33
#define I2C_SCL 32

SensirionI2CSfa3x sfa3x;
Sfa3xClass Sfa3x;

void Sfa3xClass::begin()
{
    Wire.begin(I2C_SDA, I2C_SCL, 10000UL);

    sfa3x.begin(Wire);

    startMeasurement();
}

void Sfa3xClass::read()
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
        _measures.push_back({"Error", 0.0, "Restarting", ""});
        return;
    }

    _measures.push_back({"Formaldehyde", hcho / 5.0, "", "ppb"});
    _measures.push_back({"Humidity", humidity / 100.0, "", "% RH"});
    _measures.push_back({"Temperature", temperature / 200.0, "", "Celsius"});
}

void Sfa3xClass::startMeasurement()
{
    uint16_t error;
    error = sfa3x.startContinuousMeasurement();
    if (error)
        SetError("Error trying to execute startContinuousMeasurement(): ", error);
}

void Sfa3xClass::SetError(String prefix, uint16_t error)
{

    char buffer[256];
    errorToString(error, buffer, sizeof(buffer));
    _measures.push_back({"Error", 0.0, prefix, buffer});
}
