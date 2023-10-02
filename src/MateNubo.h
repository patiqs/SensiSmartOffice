#ifndef MATENUBO_H
#define MATENUBO_H
#include "uiInterface.h"

class MateNubo : public uiInterface
{
public:
    void begin();
    void commitMeasures();
    void handleNetwork();

    void visit(InfoRecord* record);
    void visit(ErrorRecord* record);
    void visit(MeasureRecord* record);
};

#endif /* GATGETBLE_H */