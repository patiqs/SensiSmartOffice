#include "main.h"
#include "Sfa3x.h"
#include "Web.h"

ulong iteration = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("\nI2C Scanner");
  pinMode(18, OUTPUT);

  Setup_Wifi();

  Sfa3x.begin();
  String err = Sfa3x.getError();
  Serial.println(err);

  Web.begin();
}

void loop() {
  ++iteration;
  Toggle_Status_Led();
  delay(1000);

  Sfa3x.read();

  Web.clearMeasures();
  Web.setMeasure("Iteration", String(iteration));
  Web.setMeasure("Error", Sfa3x.getError());
  Web.setMeasure("Formaldehyde", String(Sfa3x.getFormaldehyde()));
  Web.setMeasure("Humidity",     String(Sfa3x.getHumidity()));
  Web.setMeasure("Temperature",  String(Sfa3x.getTemp()));

  Web.handleClient();
}
