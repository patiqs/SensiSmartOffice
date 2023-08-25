#ifndef GATGETBLE_H
#define GATGETBLE_H
#include "uiInterface.h"

class GatgetBle : public uiInterface
{
public:
    void begin();
    void commitMeasures();
    void pushMeasure(MeasureRecord measure);
    void pushMeasures(std::vector<MeasureRecord> measures);
};

#endif /* GATGETBLE_H */
