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
  Web.begin();
}

void loop() {
  Toggle_Status_Led();
  Serial.printf("loop %d\n", ++iteration);
  delay(1000);

  Sfa3x.print();
  Web.handleClient();
}
