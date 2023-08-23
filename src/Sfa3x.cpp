#include "main.h"
#include <SensirionI2CSfa3x.h>
#include "Sfa3x.h"

SensirionI2CSfa3x sfa3x;
Sfa3xClass Sfa3x;

Sfa3xClass::Sfa3xClass(/* args */)
{
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
    if (error)
    {
        Serial.print("Error trying to execute startContinuousMeasurement(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    }
}

void Sfa3xClass::print(){
      uint16_t error;
  char errorMessage[256];

  delay(1000);
  int16_t hcho;
  int16_t humidity;
  int16_t temperature;
  error = sfa3x.readMeasuredValues(hcho, humidity, temperature);
  if (error) {
      Serial.print("Error trying to execute readMeasuredValues(): ");
      errorToString(error, errorMessage, 256);
      Serial.println(errorMessage);
  } else {
      Serial.print("Hcho:");
      Serial.print(hcho / 5.0);
      Serial.print("\t");
      Serial.print("Humidity:");
      Serial.print(humidity / 100.0);
      Serial.print("\t");
      Serial.print("Temperature:");
      Serial.println(temperature / 200.0);
  }
}
