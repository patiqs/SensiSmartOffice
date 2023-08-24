#ifndef SFA3X_H
#define SFA3X_H

#include "measureRecord.h"
#include <vector>

class Sfa3xClass
{
private:
    std::vector<MeasureRecord> _measures;
    void SetError(String prefix, uint16_t error);
    void startMeasurement();

public:
    std::vector<MeasureRecord> getMeasures() { return _measures; };

    void begin();
    void read();
};

extern Sfa3xClass Sfa3x;

#endif /* SFA3X_H */
