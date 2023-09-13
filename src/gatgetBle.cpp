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
  //provider = new DataProvider(lib);
  provider->begin();
  provider->setSampleConfig(DataType::T_RH_CO2_VOC_PM25_HCHO);
  //provider->_historyIntervalMilliSeconds = 60000; //1min
  Serial.print("Sensirion GadgetBle Lib initialized with deviceId = ");
  Serial.println(provider->getDeviceIdString());
}

int x;

void GatgetBle::commitMeasures()
{
  // ++x;
  // String s = "SampleHistory: ";
  // s += provider->_sampleHistory.numberOfSamplesInHistory();
  // Serial.println(s.c_str());

   provider->writeValueToCurrentSample(provider->_historyIntervalMilliSeconds / 1000, SignalType::TEMPERATURE_DEGREES_CELSIUS);
  // provider->writeValueToCurrentSample(x % 60, SignalType::RELATIVE_HUMIDITY_PERCENTAGE);
  // provider->writeValueToCurrentSample(provider->_sampleHistory.numberOfSamplesInHistory(), SignalType::CO2_PARTS_PER_MILLION);
  // provider->writeValueToCurrentSample(provider->_sampleHistory.numberOfSamplesInHistory(), SignalType::VOC_INDEX);
  // provider->writeValueToCurrentSample(provider->_historyIntervalMilliSeconds / 1000 , SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER);
  // provider->writeValueToCurrentSample(x % 20, SignalType::HCHO_PARTS_PER_BILLION);

  provider->commitSample();
}

void GatgetBle::handleNetwork()
{
  provider->handleDownload();
}

void GatgetBle::visit(InfoRecord *record) {}
void GatgetBle::visit(ErrorRecord *record) {}
void GatgetBle::visit(MeasureRecord *record) { provider->writeValueToCurrentSample(record->Value, record->Type); }

#endif /* BLE */
