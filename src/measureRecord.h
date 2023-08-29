#ifndef MEASURERECORD_H
#define MEASURERECORD_H

#include <WString.h>
#include "Sensirion_Gadget_BLE.h"

struct MeasureRecord{
    String DeviceName;
    SignalType Type;
    float fVal;
    String sVal;
    String unit;
};

#endif /* MEASURERECORD_H */
