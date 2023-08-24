#include "main.h"
#include "Sfa3x.h"
#include "Web.h"

ulong iteration = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("\nI2C Scanner");
  pinMode(18, OUTPUT);

  Setup_Wifi_AP();

  Sfa3x.begin();

  Web.begin();
}

void loop() {
  ++iteration;
  Toggle_Status_Led();
  delay(1000);

  Sfa3x.read();

  Web.clearMeasures();

  Web.pushMeasure({"iteration", iteration * 1.0, "", ""});
  Web.pushMeasures(Sfa3x.getMeasures());

  Web.handleClient();
}
