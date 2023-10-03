#if defined(NuboLcdBLE) 
#include "LiquidCrystal_I2C.h"
#include "displayHandler.h"
#include "access.h"



LiquidCrystal_I2C lcd(0x27, 16, 2);
String Map(SignalType st);

void displayHandler::begin()
{
  lcd.init();
  lcd.backlight();
  Serial.println("LCD display started");
}

void displayHandler::commitMeasures()
{
}

String HumiStr = " Humidity: ";
String PercentStr = "%";
String TempStr = " Temp: ";
String CelsStr = "C";
//lcd.print((char)223); //degree sign
String CO2Str = " CO2: ";
String PpmStr = "ppm";
String VocStr = " VocIndex: ";
String NoxStr = " NoxIndex: ";
String Pm2p5Str = " Pm2p5: ";
String micropercubicmeterStr = "ug/m3"; 

float dispTemperatureVal;
float dispHumidityVal;
uint32_t dispCO2Val;
uint32_t dispPM2P5Val;
uint32_t dispVOCVal;
uint32_t dispNOXVal;


void displayHandler::handleNetwork() // handling the lcd display
{

    String line1 = "";
    String line2 = "";
    String line3 = "";
    String line4 = "";

  std::for_each(_records.rbegin(), _records.rend(), [&](String record)
                { line1 += record; });
  //_records.clear();

    if (!globalState){
      line1 += TempStr;
      line1 += String(dispTemperatureVal);
      line1 += String((char)223);
      line1 += CelsStr;

      line3 += HumiStr;
      line3 += String(dispHumidityVal);
      line3 += PercentStr;
      


    }
    else {
      line1 += CO2Str;
      line1 += String(dispCO2Val);

      line2 += PpmStr;
      line2 += String(dispPM2P5Val);

      line3 += VocStr;
      line3 += String(dispVOCVal);
      
      line4 += NoxStr;
      line4 += String(dispNOXVal);

    }

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(line1);
    lcd.setCursor(0,1);
    lcd.print(line2);
    lcd.setCursor(0,2);
    lcd.print(line3);
    lcd.setCursor(0,3);
    lcd.print(line4);

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
