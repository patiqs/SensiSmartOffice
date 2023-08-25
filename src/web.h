#ifndef WEB_H
#define WEB_H

#include "uiInterface.h"

class Web : public uiInterface
{
public:
    Web(/* args */);
    void handle_root();

    void begin();
    void pushMeasure(MeasureRecord measure);
    void pushMeasures(std::vector<MeasureRecord> measures);
    void commitMeasures();
};

#endif /* WEB_H */