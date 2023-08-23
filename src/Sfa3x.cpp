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
    Wire.begin();

    sfa3x.begin(Wire);

    uint16_t error;
    char errorMessage[256];

    sfa3x.begin(Wire);

    // Start Measurement
    error = sfa3x.startContinuousMeasurement();
    SetError(error, "Error trying to execute startContinuousMeasurement(): ", [](Sfa3xClass* instance){});
}

void Sfa3xClass::read(){
  uint16_t error;

  error = sfa3x.readMeasuredValues(_hcho, _humidity, _temperature);
  SetError(error, "Error trying to execute readMeasuredValues(): ", [](Sfa3xClass* instance){
      Serial.print("Hcho:");
      Serial.print(instance->_hcho / 5.0);
      Serial.print("\t");
      Serial.print("Humidity:");
      Serial.print(instance->_humidity / 100.0);
      Serial.print("\t");
      Serial.print("Temperature:");
      Serial.println(instance->_temperature / 200.0);
  });

}

void Sfa3xClass::SetError(uint16_t error, String prefix, std::function<void(Sfa3xClass*)> onSuccess){
    if (error)
    {
        char buffer[256];
        errorToString(error, buffer, sizeof(buffer));
        _error = prefix + buffer;
    }
    else{
        _error = "No error";
        onSuccess(this);
    }
}