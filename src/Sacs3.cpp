#include "Sacs3.h"

//
// static int measurementIntervalMs = 5100;
//

void SACS3Sensor::begin()
{

    attachInterrupt(digitalPinToInterrupt(interruptPin), LowPulse, FALLING);
    
}

void SACS3Sensor::read()
{


    if (boolTSyncFoundState == false) {
        _parent->push(new InfoRecord(_name, "Detecting synchronization pulse."));
        pushRecords();
        FindTSync();
        return;
    }
    else if (boolTSyncFoundState == true && MachineState == 1) { 
        ulTSyncTime = ulTimeDifInMicros;
        MachineState++;
        return;
    }
    else if (boolTSyncFoundState == true && MachineState == 3) {
        ulTTempTime = ulTimeDifInMicros; 
        MachineState++;  
        return; 
    }
    else if (boolTSyncFoundState == true && MachineState == 5) { 
        ulTRHTime = ulTimeDifInMicros; 
        boolNewValueRegistered = true;
        MachineState = 0;  
        return;
    }

    
    if (millis() - lastMeasurementTimeMs < measurementIntervalMs)
    {
        _parent->push(new InfoRecord(_name, "Waiting for next data"));
        pushRecords();
        return;
    };
    lastMeasurementTimeMs = millis();
    uint16_t error;

    error = sen5x.readMeasuredValues(massConcentrationPm1p0, massConcentrationPm2p5, massConcentrationPm4p0, massConcentrationPm10p0, ambientHumidity, ambientTemperature, vocIndex, noxIndex);
    if (error)
    {
        HandleError("Error trying to execute readMeasuredValues(): ", error);
        error = sen5x.deviceReset();
        HandleError("Error trying to execute deviceReset(): ", error);
        startMeasurement();
        return;
    }
    if (ambientHumidity == 0 && ambientTemperature == 0)
    {
        startMeasurement();
        _parent->push(new ErrorRecord(_name, "Restarting"));
        return;
    }

    pushRecords();
}



void SACS3Sensor::pushRecords()
{
    _parent->push(new MeasureRecord(_name, SignalType::RELATIVE_HUMIDITY_PERCENTAGE, ambientHumidity));
    _parent->push(new MeasureRecord(_name, SignalType::TEMPERATURE_DEGREES_CELSIUS, ambientTemperature));
    //_parent->push(new MeasureRecord(_name, SignalType::NOX_INDEX, noxIndex));
}



void SACS3Sensor::startMeasurement()
{
    uint16_t error;
    error = sen5x.startMeasurement();
    HandleError("Error trying to execute startContinuousMeasurement(): ", error);
}



IRAM_ATTR void SACS3Sensor::pulseISR()
{
    ulNewTimeInMicros = micros(); // Returns the number of microseconds since the Arduino board began running the current program. 
    // This number will overflow (go back to zero), after approximately 70 minutes.
    ulTimeDifInMicros = ulNewTimeInMicros - ulLastTimeInMicros; 
    ulLastTimeInMicros = ulNewTimeInMicros;
    if(boolTSyncFoundState == true) MachineState++;

}



void SACS3Sensor::FindTSync()
{
  if (ulTimeDifInMicros > 170000 && ulTimeDifInMicros < 240000) {
    boolTSyncFoundState = true;
    MachineState++;
     }
}