#ifdef BLE
#include "gatgetBle.h"
#include "Sensirion_Gadget_BLE.h"

NimBLELibraryWrapper lib;
DataProvider *provider;

void GatgetBle::begin()
{
  sampleConfigSelector[DataType::T_RH_V3].sampleType = (uint8_t)-1;
  provider = new DataProvider(lib);
  provider->begin();
  provider->setSampleConfig(DataType::T_RH_CO2_VOC_PM25_HCHO_V2);
  Serial.print("Sensirion GadgetBle Lib initialized with deviceId = ");
  Serial.println(provider->getDeviceIdString());
}

void GatgetBle::commitMeasures()
{
  provider->commitSample();
  provider->handleDownload();
}

void GatgetBle::visit(InfoRecord *record) {}
void GatgetBle::visit(ErrorRecord *record) {}
void GatgetBle::visit(MeasureRecord *record) { provider->writeValueToCurrentSample(record->Value, record->Type); }

#endif /* BLE */
