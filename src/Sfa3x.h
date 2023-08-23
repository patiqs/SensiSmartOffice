#ifndef SFA3X_H
#define SFA3X_H

class Sfa3xClass
{
private:
    int16_t _hcho;
    int16_t _humidity;
    int16_t _temperature;
    String _error;
    void SetError(uint16_t error, String prefix, std::function<void(Sfa3xClass*)> onSuccess);

public:
    Sfa3xClass(/* args */);
    ~Sfa3xClass();

    String getError() { return _error; }

    void begin();
    void read();
};

extern Sfa3xClass Sfa3x;

#endif /* SFA3X_H */
