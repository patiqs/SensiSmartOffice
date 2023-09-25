#ifndef SACS3_H
#define SACS3_H

#include "sensor.h"

class SACS3Sensor : public Sensor
{
private:
    float relativehumidity = 0.0f;
    float temperatureincelsius = 0.0f;
    float temperatureinfahrenheit = 0.0f;

    unsigned long ulNewTimeInMicros = 0; 
    unsigned long ulPrevTimeInMicros = 0;
    unsigned long ulTimeDifInMicros = 0;

    unsigned long ulTSyncTime = 0;
    unsigned long ulTTempTime = 0;
    unsigned long ulTRHTime = 0;

    bool boolTSyncFoundState = false;
    bool boolLedState = false;
    bool boolNewValueRegistered = false;

    unsigned short SACS3MachineState = 0;

/*  Machine States
 *    0 = In T_Sync period 
 *    1 = In T_Temp period  
 *    2 = In T_RH period  
 */

    int64_t lastMeasurementTimeMs = 0;
    
    void FindTSync();
    void ExtractData(); 
    void pushRecords();
    void StateReset();


public:
    SACS3Sensor(const char *name, SensorContainer *parent) : Sensor(name, parent){};

    void begin();
    IRAM_ATTR void pulseISR();
    void read();


};

#endif /* SACS3_H */
