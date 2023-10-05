#ifndef SACS3_H
#define SACS3_H

#include "sensor.h"

IRAM_ATTR void SACS3InterruptHandler();

class Sacs3Sensor : public Sensor
{
private:

    #define SACS3interruptPin 14

    float float_SACS3relativeHumidity = 0.0f;
    float float_SACS3temperatureInCelsius = 0.0f;
    float float_SACS3temperatureInFahrenheit = 0.0f;

    uint32_t uint32_TSyncTime = 0;
    uint32_t uint32_TTempTime = 0;
    uint32_t uint32_TRHTime = 0;

    bool bool_TSyncFoundState = false;

    byte uint8_SACS3MachineState = 0;

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
