#include "Sacs3.h"


    static uint32_t ulNewTimeInMicros = 0; 
    static uint32_t ulPrevTimeInMicros = 0;
    static uint32_t ulTimeDifInMicros = 0;
    static bool boolNewValueRegistered = false;

IRAM_ATTR void SACS3InterruptHandler()
{
    ulNewTimeInMicros = micros(); // Returns the number of microseconds since the Arduino board began running the current program. 
    // This number will overflow (go back to zero), after approximately 70 minutes.
    ulTimeDifInMicros = ulNewTimeInMicros - ulPrevTimeInMicros;
    ulPrevTimeInMicros = ulNewTimeInMicros;
    boolNewValueRegistered = true; 
}


void Sacs3Sensor::begin()
{
    StateReset();
    attachInterrupt(digitalPinToInterrupt(SACS3interruptPin), SACS3InterruptHandler, FALLING); 
    while(!bool_TSyncFoundState) FindTSync(); 
}


void Sacs3Sensor::read()
{
    if(bool_TSyncFoundState){
        if(boolNewValueRegistered && uint8_SACS3MachineState == 0) {
            uint32_TSyncTime = ulTimeDifInMicros;
            boolNewValueRegistered = false; 
            uint8_SACS3MachineState++;    
        }
        if(boolNewValueRegistered && uint8_SACS3MachineState == 1) {
            uint32_TTempTime = ulTimeDifInMicros;
            boolNewValueRegistered = false;
            uint8_SACS3MachineState++;
        }
        if(boolNewValueRegistered && uint8_SACS3MachineState == 2) {
            uint32_TRHTime = ulTimeDifInMicros;
            boolNewValueRegistered = false;
            uint8_SACS3MachineState = 0;    
        }
    
    
    ExtractData(); 
    pushRecords(); 
    }
}



void Sacs3Sensor::pushRecords()
{
    if(float_SACS3temperatureInCelsius > -40 || float_SACS3temperatureInCelsius < 90) {
        _parent->push(new MeasureRecord(_name, SignalType::TEMPERATURE_DEGREES_CELSIUS, float_SACS3temperatureInCelsius));
    }
    else { // Discard data, probably TSync period was lost. 
        bool_TSyncFoundState = false;
        FindTSync();
    }
    
    //    _parent->push(new MeasureRecord(_name, SignalType::TEMPERATURE_DEGREES_FAHRENHEIT, temperatureinfahrenheit));


    if(float_SACS3relativeHumidity > 0 || float_SACS3relativeHumidity < 100) {
        _parent->push(new MeasureRecord(_name, SignalType::RELATIVE_HUMIDITY_PERCENTAGE, float_SACS3relativeHumidity));
    }
    else { // Discard data, probably TSync period was lost. 
        bool_TSyncFoundState = false;
        FindTSync();
    }
}



void Sacs3Sensor::ExtractData()
{
  float_SACS3temperatureInCelsius = (((uint32_TTempTime/(float)uint32_TSyncTime)*131104-14472)/51095.0)*175-45 ; 
  float_SACS3relativeHumidity = (((uint32_TRHTime/(float)uint32_TSyncTime)*131104-14472)/51095.0)*100 ;
}



void Sacs3Sensor::FindTSync()
{
    if(boolNewValueRegistered){
        if (ulTimeDifInMicros > 170000 || ulTimeDifInMicros < 230000) {
            bool_TSyncFoundState = true;
            uint8_SACS3MachineState = 0;
            boolNewValueRegistered = false;

        }
        else {
            bool_TSyncFoundState == false;
            boolNewValueRegistered = false;
        }
    }
}



void Sacs3Sensor::StateReset()
{
 // if the sensor is removed and reconnected, the device may lose T_Sync period, which therefore must be found again 
        bool_TSyncFoundState = false;
        boolNewValueRegistered = false;
        uint8_SACS3MachineState = 0;
        ulNewTimeInMicros = 0;
        ulPrevTimeInMicros = 0;
        ulTimeDifInMicros = 0;
        uint32_TSyncTime = 0;
        uint32_TTempTime = 0;
        uint32_TRHTime = 0;
    

}