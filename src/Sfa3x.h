#ifndef SFA3X_H
#define SFA3X_H

class Sfa3xClass
{
private:
    double _hcho;
    double _humidity;
    double _temperature;
    String _error;
    void SetError(String prefix, uint16_t error);

public:
    Sfa3xClass(/* args */);
    ~Sfa3xClass();

    String getError() { return _error; }
    double getFormaldehyde() { return _hcho; };
    double getHumidity() { return _humidity; };
    double getTemp() { return _temperature; };

    void begin();
    void read();
};

extern Sfa3xClass Sfa3x;

#endif /* SFA3X_H */
