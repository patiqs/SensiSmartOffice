#include "Sacs3.h"


void SACS3Sensor::begin()
{
    StateReset();
    attachInterrupt(digitalPinToInterrupt(interruptPin), InterruptHandler, FALLING); 
    while(!boolTSyncFoundState) FindTSync(); 
}


void SACS3Sensor::read()
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



void SACS3Sensor::pushRecords()
{
    if(relativehumidity > 0 || relativehumidity < 100) {
        _parent->push(new MeasureRecord(_name, SignalType::RELATIVE_HUMIDITY_PERCENTAGE, relativehumidity));
    }
    else { // Discard data, probably TSync period was lost. 
        HandleError("Invalid humidity reading. ", error);
        boolTSyncFoundState = false;
        FindTSync();
    }

    if(temperatureincelsius > -40 || temperatureincelsius < 90) {
        _parent->push(new MeasureRecord(_name, SignalType::TEMPERATURE_DEGREES_CELSIUS, temperatureincelsius));
    }
    else { // Discard data, probably TSync period was lost. 
        HandleError("Invalid temperature reading. ", error);
        boolTSyncFoundState = false;
        FindTSync();
    }
    //    _parent->push(new MeasureRecord(_name, SignalType::TEMPERATURE_DEGREES_FAHRENHEIT, temperatureinfahrenheit));
}



void SACS3Sensor::ExtractData()
{
  temperatureincelsius = (((ulTTempTime/(float)ulTSyncTime)*131104-14472)/51095.0)*175-45 ; 
  relativehumidity = (((ulTRHTime/(float)ulTSyncTime)*131104-14472)/51095.0)*100 ;
}



IRAM_ATTR void SACS3Sensor::InterruptHandler()
{
    ulNewTimeInMicros = micros(); // Returns the number of microseconds since the Arduino board began running the current program. 
    // This number will overflow (go back to zero), after approximately 70 minutes.
    ulTimeDifInMicros = ulNewTimeInMicros - ulPrevTimeInMicros;
    ulPrevTimeInMicros = ulNewTimeInMicros;
    boolNewValueRegistered = true; 
}



void SACS3Sensor::FindTSync()
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



void SAC3Sensor::StateReset()
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

}