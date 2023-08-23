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

  Web.setIteration(iteration);

  String err = Sfa3x.getError();
  Serial.println(err);
  Web.setError(err);

  Web.handleClient();
}
