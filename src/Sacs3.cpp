#include "Sacs3.h"


    static uint32_t ulNewTimeInMicros = 0; 
    static uint32_t ulPrevTimeInMicros = 0;
    static uint32_t ulTimeDifInMicros = 0;
    static bool boolNewValueRegistered = false;

IRAM_ATTR void InterruptHandler()
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
    attachInterrupt(digitalPinToInterrupt(interruptPin), InterruptHandler, FALLING); 
    while(!boolTSyncFoundState) FindTSync(); 
}


void Sacs3Sensor::read()
{
    if(boolTSyncFoundState){
        if(boolNewValueRegistered && SACS3MachineState == 0) {
            ulTSyncTime = ulTimeDifInMicros;
            boolNewValueRegistered = false; 
            SACS3MachineState++;    
        }
        if(boolNewValueRegistered && SACS3MachineState == 1) {
            ulTTempTime = ulTimeDifInMicros;
            boolNewValueRegistered = false;
            SACS3MachineState++;
        }
        if(boolNewValueRegistered && SACS3MachineState == 2) {
            ulTRHTime = ulTimeDifInMicros;
            boolNewValueRegistered = false;
            SACS3MachineState = 0;    
        }
    
    
    ExtractData(); 
    pushRecords(); 
    }
}



void Sacs3Sensor::pushRecords()
{
    if(relativehumidity > 0 || relativehumidity < 100) {
        _parent->push(new MeasureRecord(_name, SignalType::RELATIVE_HUMIDITY_PERCENTAGE, relativehumidity));
    }
    else { // Discard data, probably TSync period was lost. 
        boolTSyncFoundState = false;
        FindTSync();
    }

    if(temperatureincelsius > -40 || temperatureincelsius < 90) {
        _parent->push(new MeasureRecord(_name, SignalType::TEMPERATURE_DEGREES_CELSIUS, temperatureincelsius));
    }
    else { // Discard data, probably TSync period was lost. 
        boolTSyncFoundState = false;
        FindTSync();
    }
    //    _parent->push(new MeasureRecord(_name, SignalType::TEMPERATURE_DEGREES_FAHRENHEIT, temperatureinfahrenheit));
}



void Sacs3Sensor::ExtractData()
{
  temperatureincelsius = (((ulTTempTime/(float)ulTSyncTime)*131104-14472)/51095.0)*175-45 ; 
  relativehumidity = (((ulTRHTime/(float)ulTSyncTime)*131104-14472)/51095.0)*100 ;
}



void Sacs3Sensor::FindTSync()
{
    if(boolNewValueRegistered){
        if (ulTimeDifInMicros > 170000 || ulTimeDifInMicros < 230000) {
            boolTSyncFoundState = true;
            SACS3MachineState = 0;
            boolNewValueRegistered = false;

        }
        else {
            boolTSyncFoundState == false;
            boolNewValueRegistered = false;
        }
    }
}



void Sacs3Sensor::StateReset()
{
 // if the sensor is removed and reconnected, the device may lose T_Sync period, which therefore must be found again 
        boolTSyncFoundState = false;
        boolNewValueRegistered = false;
        SACS3MachineState = 0;
        ulNewTimeInMicros = 0;
        ulPrevTimeInMicros = 0;
        ulTimeDifInMicros = 0;
        ulTSyncTime = 0;
        ulTTempTime = 0;
        ulTRHTime = 0;
    

}