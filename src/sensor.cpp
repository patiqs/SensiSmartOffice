#include "sensor.h"
#include "SensirionErrors.h"

void Sensor::HandleError(String prefix, uint16_t error)
{
    if (!error) return;
    char buffer[256];
    errorToString(error, buffer, sizeof(buffer));
    _parent->push(new ErrorRecord(_name, prefix + buffer));
}
