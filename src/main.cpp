#include "main.h"
#include <SensirionI2CSfa3x.h>

ulong iteration = 0;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println("\nI2C Scanner");
  pinMode(18, OUTPUT);
}

void loop() {
  Toggle_Status_Led();
  Serial.printf("loop %d\n", ++iteration);
  delay(500);
}
