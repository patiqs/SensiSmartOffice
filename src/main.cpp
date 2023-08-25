#include "main.h"
#include "Sfa3x.h"
#ifdef WEB
#include "Web.h"
#endif
#ifdef BLE
#include "gatgetBle.h"
#endif

uiInterface *ui;
ulong iteration = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("\nI2C Scanner");
  pinMode(18, OUTPUT);

  Sfa3x.begin();

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

  Sfa3x.read();

#ifdef WEB
  ui->clearMeasures();

  ui->pushMeasure({"iteration", iteration * 1.0, "", ""});
  ui->pushMeasures(Sfa3x.getMeasures());

  ui->commitMeasures();
#endif
}
