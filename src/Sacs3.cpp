#include "Sacs3.h"


void SACS3Sensor::begin()
{
    attachInterrupt(digitalPinToInterrupt(interruptPin), LowPulse, FALLING);  
}

void SACS3Sensor::read()
{
    IsEvalStateRight();
    FindTSync();

    ExtractData();

    pushRecords();
}



void SACS3Sensor::pushRecords()
{
    _parent->push(new MeasureRecord(_name, SignalType::RELATIVE_HUMIDITY_PERCENTAGE, relativehumidity));
    _parent->push(new MeasureRecord(_name, SignalType::TEMPERATURE_DEGREES_CELSIUS, temperatureincelsius));
//    _parent->push(new MeasureRecord(_name, SignalType::TEMPERATURE_DEGREES_FAHRENHEIT, temperatureinfahrenheit));
}



void SACS3Sensor::ExtractData()
{
  ftemp = (((ulTTempTime/(float)ulTSyncTime)*131104-14472)/51095.0)*175-45 ; 
  fhumidity = (((ulTRHTime/(float)ulTSyncTime)*131104-14472)/51095.0)*100 ;
}



IRAM_ATTR void SACS3Sensor::pulseISR()
{
    ulNewTimeInMicros = micros(); // Returns the number of microseconds since the Arduino board began running the current program. 
    // This number will overflow (go back to zero), after approximately 70 minutes.
    ulTimeDifInMicros = ulNewTimeInMicros - ulLastTimeInMicros; 
    ulLastTimeInMicros = ulNewTimeInMicros;
    if(boolTSyncFoundState == true) {
        if (SACS3MachineState == 0) { 
        ulTSyncTime = ulTimeDifInMicros;
        SACS3MachineState++;
        }
        else if (SACS3MachineState == 1){
        ulTTempTime = ulTimeDifInMicros; 
        SACS3MachineState++;  
        }
        else if (SACS3MachineState == 2){
        ulTRHTime = ulTimeDifInMicros; 
        SACS3MachineState = 0;  
        }
    }
}



void SACS3Sensor::FindTSync()
{
    while(!boolTSyncFoundState) {
        if (ulTimeDifInMicros < 170000 && ulTimeDifInMicros > 240000) {
            boolTSyncFoundState == false;
        }
        else {
            boolTSyncFoundState = true;
            SACS3MachineState = 0;
        }
    }
}



void SAC3Sensor::IsEvalStateRight()
{
    if (ulTSyncTime < 170000 && ulTSyncTime != 0) { // if the sensor is removed and reconnected, the device may lose T_Sync period, which therefore must be found again 
        boolTSyncFoundState = false;
        SACS3MachineState = 0;
        ulNewTimeInMicros = 0;
        ulLastTimeInMicros = 0;
        ulTimeDifInMicros = 0;
        ulTSyncTime = 0;
        ulTTempTime = 0;
        ulTRHTime = 0;
    }

}