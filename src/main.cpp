#include "main.h"
#include "Sfa3x.h"
#include "sensorContainer.h"
#ifdef WEB
#include "Web.h"
#endif
#ifdef BLE
#include "gatgetBle.h"
#endif

uiInterface *ui;
ulong iteration = 0;
SensorContainer sensors;

void setup()
{
  Serial.begin(115200);
  Serial.println("\nI2C Scanner");
  pinMode(18, OUTPUT);

  sensors.begin();

#ifdef WEB
  Setup_Wifi_AP();
  ui = new Web();
#endif
#ifdef BLE
  ui = new GatgetBle();
#endif
  ui->begin();
}

void loop()
{
  ++iteration;
  Toggle_Status_Led();
  delay(1000);

  auto info = InfoRecord("Iteration", String(iteration));
  ui->visit(&info);

  sensors.read();

  sensors.print(ui);

  ui->commitMeasures();
}
