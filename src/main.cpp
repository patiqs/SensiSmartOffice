#include "Sfa3x.h"
#include "sensorContainer.h"
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

void setup()
{
  Serial.begin(115200);
  Serial.println("\nI2C Scanner");
  pinMode(18, OUTPUT);

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
}

void loop()
{
  ++iteration;

  if (millis() - measurementIntervalMs >= lastMeasurementTimeMs)
  {
    lastMeasurementTimeMs = millis();

    auto info = InfoRecord("Iteration", String(iteration));
    ui->visit(&info);

    sensors.read();

    sensors.print(ui);

    ui->commitMeasures();
    delay(500);
  };
  
  ui->handleNetwork();
  delay(3);
}
