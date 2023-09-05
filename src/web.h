#ifndef WEB_H
#define WEB_H

#include "uiInterface.h"

void Setup_Wifi();
void Setup_Wifi_AP();

class Web : public uiInterface
{
private:
    std::vector<String> _records;
public:
    void handle_root();

    void begin();
    void commitMeasures();
    void handleNetwork();

    void visit(InfoRecord* record);
    void visit(ErrorRecord* record);
    void visit(MeasureRecord* record);
};

#endif /* WEB_H */