#ifndef RECORD_H
#define RECORD_H

#include <WString.h>
#include "Sensirion_Gadget_BLE.h"
#include "uiInterface.h"

class uiInterface;

struct Record
{
    String DeviceName;
    Record(String deviceName);
    virtual ~Record();

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
    ~InfoRecord();

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
    ~ErrorRecord();

    void accept(uiInterface *ui);

    String toString() { return DeviceName + " > ERROR > " + Error; }
};

struct MeasureRecord : Record
{
    SignalType Type;
    float Value;

    MeasureRecord(
        String deviceName,
        SignalType type,
        float value)
        : Record(deviceName), Type(type), Value(value){};
    ~MeasureRecord();

    void accept(uiInterface *ui);

    String toString() { return DeviceName + " > " + mapName(Type) + " : " + Value + mapUnit(Type); }

    String mapName(SignalType st)
    {
        switch (st)
        {
        case SignalType::TEMPERATURE_DEGREES_CELSIUS:
            return "Temperature";
        case SignalType::RELATIVE_HUMIDITY_PERCENTAGE:
            return "Humidity";
        case SignalType::CO2_PARTS_PER_MILLION:
            return "CO2";
        case SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER:
            return "PM2.5";
        case SignalType::VOC_INDEX:
            return "VOC";
        case SignalType::NOX_INDEX:
            return "NOX";
        default:
            return "Undefined";
        }
    }

    String mapUnit(SignalType st)
    {
        switch (st)
        {
        case SignalType::TEMPERATURE_DEGREES_CELSIUS:
            return "Celsius";
        case SignalType::RELATIVE_HUMIDITY_PERCENTAGE:
            return "%";
        case SignalType::CO2_PARTS_PER_MILLION:
            return "ppm";
        case SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER:
            return "ug/m3";
        case SignalType::VOC_INDEX:
            return "";
        case SignalType::NOX_INDEX:
            return "";
        default:
            return "Undefined";
        }
    }
};

#endif /* RECORD_H */
