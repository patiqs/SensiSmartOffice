#if defined(NuboLcdBLE) 
#include "LiquidCrystal_I2C.h"
#include "displayHandler.h"
#include "access.h"



LiquidCrystal_I2C lcd(0x27, 20, 4);
String Map(SignalType st);

void displayHandler::begin()
{
  Serial.println("displayHandler begin");
  lcd.init();
  lcd.backlight();
}

void displayHandler::commitMeasures()
{
}


float dispTemperatureVal;
float dispHumidityVal;
uint32_t dispCO2Val;
uint32_t dispPM2P5Val;
uint32_t dispVOCVal;
uint32_t dispNOXVal;


void displayHandler::handleNetwork() // handling the lcd display
{

    if (!globalState){

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" Temperature: ");
        lcd.print(dispTemperatureVal);
        lcd.print("C");
        lcd.setCursor(0,2);
        lcd.print(" Humidity:    ");
        lcd.print(dispHumidityVal);
        lcd.print("%");
    }
    else {

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" CO2:      ");
        lcd.print(dispCO2Val);
        lcd.print(" ppm ");
        lcd.setCursor(0,1);
        lcd.print(" Pm2p5:    ");
        lcd.print(dispPM2P5Val);
        lcd.print(" ug/m3");
        lcd.setCursor(0,2);
        lcd.print(" VocIndex: ");
        lcd.print(dispVOCVal);
        lcd.setCursor(0,3);
        lcd.print(" NoxIndex: ");
        lcd.print(dispNOXVal);

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
    case SignalType::NOX_INDEX: dispNOXVal = record->Value; break;
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
