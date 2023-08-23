#ifndef WEB_H
#define WEB_H

class WebClass
{
private:
    

public:
    WebClass(/* args */);
    void begin();
    void handleClient();

    void handle_root();
};

extern WebClass Web;

#endif /* WEB_H */