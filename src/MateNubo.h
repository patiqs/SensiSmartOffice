#ifndef MATENUBO_H
#define MATENUBO_H

#include "uiInterface.h"

extern bool globalState;

class MateNubo : public uiInterface
{
private:
    std::vector<uiInterface*> _children;

public:
    void begin();
    void commitMeasures();
    void handleNetwork();

    void visit(InfoRecord* record);
    void visit(ErrorRecord* record);
    void visit(MeasureRecord* record);
};

#endif /*MATENUBO_H*/