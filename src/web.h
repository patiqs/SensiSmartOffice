#ifndef WEB_H
#define WEB_H
#include "measureRecord.h"
#include <map>
#include <vector>
class WebClass
{
private:
    std::vector<MeasureRecord> _measures;

public:
    WebClass(/* args */);
    void begin();
    void handleClient();

    void handle_root();

    void clearMeasures() { _measures.clear(); }
    void pushMeasure(MeasureRecord measure);
    void pushMeasures(std::vector<MeasureRecord> measures);
};

extern WebClass Web;

#endif /* WEB_H */