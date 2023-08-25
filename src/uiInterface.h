#ifndef UIINTERFACE_H
#define UIINTERFACE_H
#include <vector>
#include "measureRecord.h"

class uiInterface
{
protected:
    std::vector<MeasureRecord> _measures;

public:
    virtual void begin() = 0;
    void clearMeasures() { _measures.clear(); }
    virtual void pushMeasure(MeasureRecord measure) = 0;
    virtual void pushMeasures(std::vector<MeasureRecord> measures) = 0;
    virtual void commitMeasures() = 0;
};

#endif /* UIINTERFACE_H */
