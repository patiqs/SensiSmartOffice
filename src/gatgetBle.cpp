#ifdef BLE
#include "gatgetBle.h"
#include "Sensirion_Gadget_BLE.h"

NimBLELibraryWrapper lib;
DataProvider provider(lib, DataType::T_RH_HCHO);

void GatgetBle::begin()
{
  provider.begin();
  Serial.print("Sensirion GadgetBle Lib initialized with deviceId = ");
  Serial.println(provider.getDeviceIdString());
}

void GatgetBle::pushMeasure(MeasureRecord measure) {}

void GatgetBle::pushMeasures(std::vector<MeasureRecord> measures) {}

void GatgetBle::commitMeasures() {}

#endif /* BLE */
