#if (defined enableDisplay2x16) || (defined enableDisplay4x20)

#include "LiquidCrystal_I2C.h"
#include "displayHandler.h"
#include "access.h"

int previousState;
int globalState;

#ifdef enableDisplay2x16
    #define DisplayADDR 0x27
    #define DisplayCols 16
    #define DisplayRows 2
#endif

#ifdef enableDisplay4x20
    #define DisplayADDR 0x27
    #define DisplayCols 20
    #define DisplayRows 4
#endif

LiquidCrystal_I2C lcd(DisplayADDR, DisplayCols, DisplayRows);
String Map(SignalType st);

void displayHandler::begin()
{

    Serial.println("displayHandler begin");
    previousState = globalState;
    lcd.init();
    lcd.backlight();

    #ifdef enableDisplay2x16
        // Print these on the display on startup
        lcd.setCursor(0,0);
        lcd.print("Temp:          C");
        lcd.setCursor(0,1);
        lcd.print("Humi:          %");
    #endif

    #ifdef enableDisplay4x20
        // Print these on the display on startup
        lcd.setCursor(0,0);
        lcd.print("Temperature:       C");
        lcd.setCursor(0,2);
        lcd.print("Humidity:          %");
    #endif
}

void displayHandler::commitMeasures()
{
}

float dispTemperatureVal;
float dispHumidityVal;
float dispCO2Val;
uint32_t dispPM2P5Val;
float dispVOCVal;
uint32_t dispHCHOVal;


void displayHandler::handleNetwork() // handling the lcd display
{

    #ifdef enableDisplay2x16
        if (globalState != previousState) {
            lcd.clear();
            if (globalState == 0)  {
                lcd.setCursor(0,0);
                lcd.print("Temp:          C");
                lcd.setCursor(0,1);
                lcd.print("Humi:          %");
            }
            if (globalState == 1) {
                lcd.setCursor(0,0);
                lcd.print("CO2:         ppm");      
                lcd.setCursor(0,1);
                lcd.print("Pm2.5:     ug/m3");  
            }
            if (globalState == 2) {
                lcd.setCursor(0,0);
                lcd.print("VocIndex:       ");   
                lcd.setCursor(0,1);
                lcd.print("HCHO:        ppb"); 
            }
        previousState = globalState;      
        }

        char buffer[20];
        if (globalState == 0){
            lcd.setCursor(9,0);
            sprintf(buffer, "%.1f", dispTemperatureVal);
            lcd.print(buffer);
            lcd.setCursor(9,1);
            sprintf(buffer, "%.1f", dispHumidityVal);
            lcd.print(buffer);
        }
        if (globalState == 1)
        {
            lcd.setCursor(7,0);
            sprintf(buffer, "%-4.0f", dispCO2Val);
            lcd.print(buffer);
            lcd.setCursor(7,1);
            sprintf(buffer, "%-3d", dispPM2P5Val);
            lcd.print(buffer);
        }
        if (globalState == 2)
        {
            lcd.setCursor(10,0);
            sprintf(buffer, "%-4.0f", dispVOCVal);
            lcd.print(buffer);
            lcd.setCursor(8,1);
            sprintf(buffer, "%-3d", dispHCHOVal);
            lcd.print(buffer);
        }
    #endif

    #ifdef enableDisplay4x20
        if (globalState != previousState) {
            lcd.clear();
            if (globalState == 0)  {
                lcd.setCursor(0,0);
                lcd.print("Temperature:       C");
                lcd.setCursor(0,2);
                lcd.print("Humidity:          %");
            }
            if (globalState == 1) {
                lcd.setCursor(0,0);
                lcd.print("CO2:             ppm");      
                lcd.setCursor(0,1);
                lcd.print("Pm2.5:         ug/m3");  
                lcd.setCursor(0,2);
                lcd.print("VocIndex:           "); 
            }
        previousState = globalState;      
        }

        char buffer[20];
        if (globalState == 0){
            lcd.setCursor(14,0);
            sprintf(buffer, "%.1f", dispTemperatureVal);
            lcd.print(buffer);
            lcd.setCursor(14,2);
            sprintf(buffer, "%.1f", dispHumidityVal);
            lcd.print(buffer);
        }
        if (globalState == 1)
        {
            lcd.setCursor(11,0);
            sprintf(buffer, "%-4.0f", dispCO2Val);
            lcd.print(buffer);
            lcd.setCursor(11,1);
            sprintf(buffer, "%-2d", dispPM2P5Val);
            lcd.print(buffer);
            lcd.setCursor(11,2);
            sprintf(buffer, "%-4.0f", dispVOCVal);
            lcd.print(buffer);
        }
    #endif
}

  //server->send(200, "text/html", response.c_str());

void displayHandler::visit(InfoRecord *record) { }
void displayHandler::visit(ErrorRecord *record) { }
void displayHandler::visit(MeasureRecord *record) { 
    switch (record->Type) {
    case SignalType::TEMPERATURE_DEGREES_CELSIUS: dispTemperatureVal = record->Value; break; 
    case SignalType::RELATIVE_HUMIDITY_PERCENTAGE: dispHumidityVal = record->Value; break;
    case SignalType::CO2_PARTS_PER_MILLION: dispCO2Val = record->Value; break;
    case SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER: dispPM2P5Val = record->Value; break;
    case SignalType::VOC_INDEX: dispVOCVal = record->Value; break;
    case SignalType::HCHO_PARTS_PER_BILLION: dispHCHOVal = record->Value; break;
    }
}

void displayHandler::push_back(String entry)
{
  _records.push_back(entry);
  while (_records.size() > 30)
  {
    _records.erase(_records.begin());
  }
}


#endif /* enableDisplay */