#ifndef MEASURERECORD_H
#define MEASURERECORD_H

#include <WString.h>
#include "Sensirion_Gadget_BLE.h"
#include "uiInterface.h"

class uiInterface;

struct Record
{
    String DeviceName;
    Record(String deviceName) : DeviceName(deviceName){};

    virtual String toString() = 0;

    virtual void accept(uiInterface *ui) = 0;
};

struct InfoRecord : Record
{
    String Info;
    InfoRecord(
        String deviceName,
        String info)
        : Record(deviceName), Info(info){};

    String toString() { return DeviceName + " > " + Info; }

    void accept(uiInterface *ui);
};

struct ErrorRecord : Record
{
    String Error;
    ErrorRecord(
        String deviceName,
        String error)
        : Record(deviceName), Error(error){};

    void accept(uiInterface *ui);

    String toString() { return DeviceName + " > ERROR > " + Error; }
};

struct MeasureRecord : Record
{
    SignalType Type;
    float Value;
    String Unit;

    MeasureRecord(
        String deviceName,
        SignalType type,
        float value,
        String unit)
        : Record(deviceName), Type(type), Value(value), Unit(unit){};

    void accept(uiInterface *ui);

    String toString() { return DeviceName + " > " + map(Type) + " : " + Value + Unit; }

    String map(SignalType st)
    {
        switch (st)
        {
        case SignalType::TEMPERATURE_DEGREES_CELSIUS:
            return "Temperature";
        case SignalType::RELATIVE_HUMIDITY_PERCENTAGE:
            return "Humidity";
        case SignalType::CO2_PARTS_PER_MILLION:
            return "CO2";
        case SignalType::HCHO_PARTS_PER_BILLION:
            return "Formaldehyde";
        default:
            return "Undefined";
        }
    }
};

#endif /* MEASURERECORD_H */
