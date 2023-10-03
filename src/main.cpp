#include "sensorContainer.h"
#include "Sen5x.h"
#include "Scd4x.h"
#include <Bounce2.h>
#ifdef WEB
#include "Web.h"
#endif
#ifdef BLE
#include "gatgetBle.h"
#endif
#ifdef Compaund
#include "compaundUi.h"
#endif
#if NuboLcdBLE
#include "MateNubo.h"
#endif


bool globalState = 0;
const byte BUTTON_PIN = 2; /* HAS TO BE CHANGED TO THE CORRECT PIN */
Bounce b = Bounce();

uiInterface *ui;
ulong iteration = 0;
SensorContainer sensors;
static int measurementIntervalMs = 5000;
int64_t lastMeasurementTimeMs = 0;

uint16_t dispCO2Reading = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("\nI2C Scanner");
//  pinMode(18, OUTPUT);

  b.attach(BUTTON_PIN,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  b.interval(25); // Use a debounce interval of 25 milliseconds
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
#ifdef MateNubo
  ui = new MateNubo();
#endif

  ui->begin();

}

void loop()
{
  b.update(); // Update the Bounce instance
  if ( b.fell() ) globalState = !globalState;  // Call code if button transitions from HIGH to LOW

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
