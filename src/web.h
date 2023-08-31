#ifndef WEB_H
#define WEB_H

#include "uiInterface.h"

class Web : public uiInterface
{
private:
    std::vector<String> _records;
public:
    void handle_root();

    void begin();
    void commitMeasures();

    void visit(InfoRecord* record);
    void visit(ErrorRecord* record);
    void visit(MeasureRecord* record);
};

#endif /* WEB_H */