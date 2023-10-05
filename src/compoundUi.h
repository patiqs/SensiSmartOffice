#ifndef COMPOUNDUI_H
#define COMPOUNDUI_H

#include "uiInterface.h"

class CompoundUi : public uiInterface
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

#endif /*COMPOUNDUI_H*/