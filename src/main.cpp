#include "sensorContainer.h"
#include "LiquidCrystal_I2C.h"
#include "Sen5x.h"
#include "Scd4x.h"
#ifdef WEB
#include "Web.h"
#endif
#ifdef BLE
#include "gatgetBle.h"
#endif
#ifdef Compaund
#include "compaundUi.h"
#endif

uiInterface *ui;
ulong iteration = 0;
SensorContainer sensors;
static int measurementIntervalMs = 5000;
int64_t lastMeasurementTimeMs = 0;

uint16_t dispCO2Reading = 0;

Scd4xSensor Scd4;

/* Set the LCD address to 0x27 for a 16 chars and 2 line display */
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup()
{
  Serial.begin(115200);
  Serial.println("\nI2C Scanner");
//  pinMode(18, OUTPUT);

  sensors.begin();

#ifdef WEB
  ui = new Web();
#endif
#ifdef BLE
  ui = new GatgetBle();
#endif
#ifdef Compaund
  ui = new CompaundUi();
#endif

  ui->begin();

  lcd.init();
  lcd.backlight();  

}

void loop()
{
  // lcd.setCursor(0,0);
  // lcd.print("Humi: ");  
  // lcd.print();

  ++iteration;

  if (millis() - lastMeasurementTimeMs >= measurementIntervalMs)
  {

    auto info = InfoRecord("Iteration", String(iteration));
    ui->visit(&info);

    sensors.read();

    sensors.accept(ui);

    ui->commitMeasures();
    delay(500);
    Serial.print(".");
    
    lastMeasurementTimeMs = millis();    
  };
  
  ui->handleNetwork();
  delay(3);
}
