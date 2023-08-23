#include "main.h"
#include <SensirionI2CSfa3x.h>
#include "Sfa3x.h"

#define I2C_SDA 33
#define I2C_SCL 32

SensirionI2CSfa3x sfa3x;
Sfa3xClass Sfa3x;

Sfa3xClass::Sfa3xClass(/* args */)
{
    _error.reserve(256);
}

Sfa3xClass::~Sfa3xClass()
{
}

void Sfa3xClass::begin(){
    Wire.begin(I2C_SDA, I2C_SCL, 10000UL);
    //Wire.setClock(10000UL);
    //Wire.begin();

    sfa3x.begin(Wire);

    uint16_t error;
    char errorMessage[256];

    sfa3x.begin(Wire);

    // Start Measurement
    error = sfa3x.startContinuousMeasurement();
    SetError("Error trying to execute startContinuousMeasurement(): ", error);
}

void Sfa3xClass::read(){
  uint16_t error;
  int16_t hcho;
  int16_t humidity;
  int16_t temperature;

  error = sfa3x.readMeasuredValues(hcho, humidity, temperature);
  _hcho = hcho / 5.0;
  _humidity = humidity / 100.0;
  _temperature = temperature/ 200.0;

  SetError("Error trying to execute readMeasuredValues(): ", error);
}

void Sfa3xClass::SetError(String prefix, uint16_t error){
    if (error)
    {
        char buffer[256];
        errorToString(error, buffer, sizeof(buffer));
        _error = prefix + buffer;
    }
    else{
        _error = "No error";
    }
}