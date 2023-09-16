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
    unsigned long ulLastTimeInMicros = 0;
    unsigned long ulTimeDifInMicros = 0;

    unsigned long ulTSyncTime = 0;
    unsigned long ulTTempTime = 0;
    unsigned long ulTRHTime = 0;

    bool boolTSyncFoundState = false;
    bool boolLedState = false;
    bool boolNewValueRegistered = false;

    usnigned short SACS3MachineState = 0;

/*  Machine States
 *    0 = In T_Sync period 
 *    1 = T_Sync period is over, saving T_Sync period duration into ulTSyncTime variable and steping into the next (2) state
 *    2 = In T_Temp period  
 *    3 = T_Temp period is over, saving T_Temp period duration into ulTTempTime variable and steping into the next (4) state
 *    4 = In T_RH period  
 *    5 = T_RH period is over, saving T_RH period duration into ulTRHTime variable and steping into the first (0) state
 */

    int64_t lastMeasurementTimeMs = 0;
    void startMeasurement();
    void pushRecords();


public:
    SACS3Sensor(const char *name, SensorContainer *parent) : Sensor(name, parent){};

    void begin();
    void pulseISR();
    void read();
};

#endif /* SACS3_H */
