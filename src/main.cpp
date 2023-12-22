#include "sensorContainer.h"

#ifdef enableSen5x
#include "Sen5x.h"
#endif

#ifdef enableScd4x
#include "Scd4x.h"
#endif

#ifdef enableSht4x
#include "Sht4x.h"
#endif

#ifdef enableSfa3x
#include "Sfa3x.h"
#endif

#ifdef enableSacs3
#include "Sacs3.h"
#endif

#include <Bounce2.h>
#include "compoundUi.h"

extern int globalState;

#ifdef enableDisplay4x20
  #define numberOfStates 2;
#endif

#ifdef enableDisplay2x16
  #define numberOfStates 3;
#endif

#define BUTTON_PIN 27 //p27
Bounce b = Bounce();

uiInterface *ui;
ulong iteration = 0;
SensorContainer sensors;
static int measurementIntervalMs = 5000;
int64_t lastMeasurementTimeMs = 0;

void setup()
{
  globalState = 0;
  Serial.begin(115200);
  Serial.println("Wire started");

  b.attach(BUTTON_PIN, INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  b.interval(5); // Use a debounce interval of 5 milliseconds
  Serial.println("Sensor begin");  
  sensors.begin();

  ui = new CompoundUi();
  ui->begin();
}

void loop()
{
  b.update(); // Update the Bounce instance
  if (b.fell()) { // Call code if button transitions from HIGH to LOW
    globalState = (globalState + 1) % numberOfStates;
    }  

  ++iteration;

  if (millis() - lastMeasurementTimeMs >= measurementIntervalMs)
  {

    auto info = InfoRecord("Iteration", String(iteration));
    ui->visit(&info);

    sensors.read();

    sensors.accept(ui);

    ui->commitMeasures();
    delay(500);
    Serial.println(".");
    
    lastMeasurementTimeMs = millis();    

  };
  
  ui->handleNetwork();
  // delay(3);
}
