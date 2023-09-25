#include "Sacs3.h"


void SACS3Sensor::begin()
{
    attachInterrupt(digitalPinToInterrupt(interruptPin), LowPulse, FALLING); 
    StateReset();
    while(!boolTSyncFoundState) FindTSync(); 
}

void SACS3Sensor::read()
{
    while(!boolTSyncFoundState) 
    {
        FindTSync(); 
        delay(500);
    } 
    
    ExtractData(); 
    pushRecords(); 
}



void SACS3Sensor::pushRecords()
{
    if(relativehumidity > 0 || relativehumidity < 100) 
    {
        _parent->push(new MeasureRecord(_name, SignalType::RELATIVE_HUMIDITY_PERCENTAGE, relativehumidity));
    }
    else // Discard data, probably TSync period was lost
    {
        HandleError("Invalid humidity reading. ", error);
        StateReset();
    }

    if(temperatureincelsius > -40 || temperatureincelsius < 90) 
    {
        _parent->push(new MeasureRecord(_name, SignalType::TEMPERATURE_DEGREES_CELSIUS, temperatureincelsius));
    }
    else // Discard data, probably TSync period was lost
    {
        HandleError("Invalid temperature reading. ", error);
        StateReset();
    }
    //    _parent->push(new MeasureRecord(_name, SignalType::TEMPERATURE_DEGREES_FAHRENHEIT, temperatureinfahrenheit));
}



void SACS3Sensor::ExtractData()
{
  temperatureincelsius = (((ulTTempTime/(float)ulTSyncTime)*131104-14472)/51095.0)*175-45 ; 
  relativehumidity = (((ulTRHTime/(float)ulTSyncTime)*131104-14472)/51095.0)*100 ;
}




IRAM_ATTR void SACS3Sensor::pulseISR()
{
    ulNewTimeInMicros = micros(); // Returns the number of microseconds since the Arduino board began running the current program. 
    // This number will overflow (go back to zero), after approximately 70 minutes.
    if(ulTSyncTime > 170000 && ulTSyncTime != 0) {
        if (SACS3MachineState == 0) { 
        ulTSyncTime = ulNewTimeInMicros - ulPrevTimeInMicros;
        SACS3MachineState++;
        }
        else if (SACS3MachineState == 1){
        ulTTempTime = ulNewTimeInMicros - ulPrevTimeInMicros;
        SACS3MachineState++;  
        }
        else if (SACS3MachineState == 2){
        ulTRHTime = ulNewTimeInMicros - ulPrevTimeInMicros; 
        SACS3MachineState = 0;  
        }
    ulPrevTimeInMicros = ulNewTimeInMicros;
    }
}



void SACS3Sensor::FindTSync()
{
    while(!boolTSyncFoundState) {
        if (ulTimeDifInMicros < 170000 || ulTimeDifInMicros > 230000) {
            boolTSyncFoundState == false;
        }
        else {
            boolTSyncFoundState = true;
            SACS3MachineState = 0;
        }
    }
}



void SAC3Sensor::StateReset()
{
 // if the sensor is removed and reconnected, the device may lose T_Sync period, which therefore must be found again 
        boolTSyncFoundState = false;
        SACS3MachineState = 0;
        ulNewTimeInMicros = 0;
        ulPrevTimeInMicros = 0;
        ulTimeDifInMicros = 0;
        ulTSyncTime = 0;
        ulTTempTime = 0;
        ulTRHTime = 0;
    }

}