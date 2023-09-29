#include <SensirionI2CSen5x.h>
#include "Sen5x.h"

SensirionI2CSen5x sen5x;
static int measurementIntervalMs = 5100;

void Sen5xSensor::begin()
{
    sen5x.begin(Wire);
    startMeasurement();
    // lastMeasurementTimeMs = millis();
    // delay(measurementIntervalMs);
}

void Sen5xSensor::read()
{
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

void Sen5xSensor::pushRecords()
{
    _parent->push(new MeasureRecord(_name, SignalType::RELATIVE_HUMIDITY_PERCENTAGE, ambientHumidity));
    _parent->push(new MeasureRecord(_name, SignalType::TEMPERATURE_DEGREES_CELSIUS, ambientTemperature));
    //_parent->push(new MeasureRecord(_name, SignalType::NOX_INDEX, noxIndex));
    _parent->push(new MeasureRecord(_name, SignalType::VOC_INDEX, vocIndex));
    _parent->push(new MeasureRecord(_name, SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER, massConcentrationPm2p5));
}

void Sen5xSensor::startMeasurement()
{
    uint16_t error;
    error = sen5x.startMeasurement();
    HandleError("Error trying to execute startContinuousMeasurement(): ", error);
}
