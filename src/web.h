#ifndef WEB_H
#define WEB_H
#include <WString.h>
#include <map>
#include <vector>
class WebClass
{
private:
    std::vector<std::pair<String, String>> _measures;

public:
    WebClass(/* args */);
    void begin();
    void handleClient();

    void handle_root();

    void clearMeasures() {_measures.clear();}
    void setMeasure(String key, String value);
};

extern WebClass Web;

#endif /* WEB_H */