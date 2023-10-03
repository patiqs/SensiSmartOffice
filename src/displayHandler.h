#ifndef DISPL_H
#define DISPL_H

#include "uiInterface.h"
#include "LiquidCrystal_I2C.h"
#include "MateNubo.h"
#include <vector>

class displayHandler : public uiInterface
{
private:
    std::vector<String> _records;
    void push_back(String entry);

public:

    void begin();
    void commitMeasures();
    void handleNetwork();

    void visit(InfoRecord* record);
    void visit(ErrorRecord* record);
    void visit(MeasureRecord* record);
};

#endif /* DISPL_H */