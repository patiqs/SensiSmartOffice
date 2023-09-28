#ifndef SACS3_H
#define SACS3_H

#include "sensor.h"

IRAM_ATTR void InterruptHandler();

class Sacs3Sensor : public Sensor
{
private:

    const byte interruptPin = 14;

    float relativehumidity = 0.0f;
    float temperatureincelsius = 0.0f;
    float temperatureinfahrenheit = 0.0f;

    uint32_t ulTSyncTime = 0;
    uint32_t ulTTempTime = 0;
    uint32_t ulTRHTime = 0;

    bool boolTSyncFoundState = false;

    uint8_t SACS3MachineState = 0;

/*  Machine States
 *    0 = In T_Sync period 
 *    1 = In T_Temp period  
 *    2 = In T_RH period  
 */

    void FindTSync();
    void ExtractData(); 
    void pushRecords();
    void StateReset();


public:
    Sacs3Sensor(const char *name, SensorContainer *parent) : Sensor(name, parent){};

    void begin();
    void read();


};

#endif /* SACS3_H */
