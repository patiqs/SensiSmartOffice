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

String HumiStr = "Humidity: ";
String PercentStr = "%";
String TempStr = "Temp: ";
String CelsStr = "C";
//lcd.print((char)223); //degree sign
String CO2Str = "CO2: ";
String PpmStr = "ppm";
String VocStr = "VocIndex: ";
String NoxStr = "NoxIndex: ";
String Pm2p5Str = "Pm2p5: ";
String micropercubicmeterStr = "ug/m3";


void displayHandler::handleNetwork() // handling the lcd display
{
    String line1;
    String line2;
    String line3;
    String line4;

  std::for_each(_records.rbegin(), _records.rend(), [&](String record)
                { line1 += record; });
  //_records.clear();

    if (!globalState){


    }
    else {

    }


  //server->send(200, "text/html", response.c_str());
}

void displayHandler::visit(InfoRecord *record) { push_back("<p>" + record->toString() + "</p>"); }
void displayHandler::visit(ErrorRecord *record) { push_back("<p>" + record->toString() + "</p>"); }
void displayHandler::visit(MeasureRecord *record) { push_back("<p>" + record->toString() + "</p>"); }

void displayHandler::push_back(String entry)
{
  _records.push_back(entry);
  while (_records.size() > 30)
  {
    _records.erase(_records.begin());
  }
}

#endif /* NuboLcdBLE */
