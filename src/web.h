#ifndef WEB_H
#define WEB_H
#include <WString.h>

class WebClass
{
private:
    int _iteration;
    String _error;

public:
    WebClass(/* args */);
    void begin();
    void handleClient();

    void handle_root();

    void setIteration(int iteration) {_iteration = iteration; }
    void setError(String error) { _error = error; }
};

extern WebClass Web;

#endif /* WEB_H */