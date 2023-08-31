#ifndef GATGETBLE_H
#define GATGETBLE_H
#include "uiInterface.h"

class GatgetBle : public uiInterface
{
public:
    void begin();
    void commitMeasures();

    void visit(InfoRecord* record);
    void visit(ErrorRecord* record);
    void visit(MeasureRecord* record);
};

#endif /* GATGETBLE_H */
