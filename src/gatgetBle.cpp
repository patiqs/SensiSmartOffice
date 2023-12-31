#if defined(BLE) || defined(Compaund)
#include "gatgetBle.h"
#include "Sensirion_Gadget_BLE.h"
#include "WifiMultiLibraryWrapper.h"

NimBLELibraryWrapper lib;
WifiMultiLibraryWrapper wifi;

DataProvider *provider;

void GatgetBle::begin()
{
  sampleConfigSelector[DataType::T_RH_V3].sampleType = (uint8_t)-1;
  provider = new DataProvider(lib, DataType::T_RH_V3, true, false, &wifi);
  provider->begin();
  provider->setSampleConfig(DataType::T_RH_CO2_VOC_PM25_HCHO);
  Serial.print("Sensirion GadgetBle Lib initialized with deviceId = ");
  Serial.println(provider->getDeviceIdString());
}

int x;

void GatgetBle::commitMeasures()
{
  provider->commitSample();
}

void GatgetBle::handleNetwork()
{
  provider->handleDownload();
}

void GatgetBle::visit(InfoRecord *record) {}
void GatgetBle::visit(ErrorRecord *record) {}
void GatgetBle::visit(MeasureRecord *record)
{
  switch (record->Type)
  {
  case SignalType::RELATIVE_HUMIDITY_PERCENTAGE:
  case SignalType::TEMPERATURE_DEGREES_CELSIUS:
  case SignalType::VOC_INDEX:
  case SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER:
  case SignalType::HCHO_PARTS_PER_BILLION:
  case SignalType::CO2_PARTS_PER_MILLION:
    provider->writeValueToCurrentSample(record->Value, record->Type);
    break;
  default:
    break;
  }
}

#endif /* BLE */
