#if defined(NuboLcdBLE) 
#include "LiquidCrystal_I2C.h"
#include "displayHandler.h"
#include "access.h"

bool previousState = 0;

LiquidCrystal_I2C lcd(0x27, 20, 4);
String Map(SignalType st);

void displayHandler::begin()
{
  Serial.println("displayHandler begin");
  lcd.init();
  lcd.backlight();

    // Print these test on the display on startup
    lcd.setCursor(0,0);
    lcd.print(" Temperature:      C");
    lcd.setCursor(0,2);
    lcd.print(" Humidity:         %");
}

void displayHandler::commitMeasures()
{
}


float dispTemperatureVal;
float dispHumidityVal;
uint32_t dispCO2Val;
uint32_t dispPM2P5Val;
uint32_t dispVOCVal;


void displayHandler::handleNetwork() // handling the lcd display
{
    if (globalState != previousState) {
        lcd.clear();
        if (!globalState)
        {
            lcd.setCursor(0,0);
            lcd.print(" Temperature:      C");
            lcd.setCursor(0,2);
            lcd.print(" Humidity:         %");
        }
        else {
            lcd.setCursor(0,0);
            lcd.print(" CO2:           ppm ");      
            lcd.setCursor(0,1);
            lcd.print(" Pm2.5:       ug/m3 ");  
            lcd.setCursor(0,2);
            lcd.print(" VocIndex:        "); 
        }
    previousState = globalState;      
    }

    char buffer[20];
    if (!globalState){
        lcd.setCursor(14,0);
        sprintf(buffer, "%.1f", dispTemperatureVal);
        lcd.print(buffer);
        lcd.setCursor(14,2);
        sprintf(buffer, "%.1f", dispHumidityVal);
        lcd.print(buffer);
    }
    else {
        lcd.setCursor(11,0);
        sprintf(buffer, "%d", dispCO2Val);
        lcd.print(buffer);
        lcd.setCursor(11,1);
        sprintf(buffer, "%d", dispPM2P5Val);
        lcd.print(buffer);
        lcd.setCursor(11,2);
        sprintf(buffer, "%d", dispVOCVal);
        lcd.print(buffer);
    }
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

#endif /* NuboLcdBLE */
