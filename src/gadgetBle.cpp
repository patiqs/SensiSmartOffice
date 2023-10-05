#ifdef enableBLE 
#include "gadgetBle.h"
#include "Sensirion_Gadget_BLE.h"
//#include "WifiMultiLibraryWrapper.h"

NimBLELibraryWrapper lib;
//WifiMultiLibraryWrapper wifi;

DataProvider *provider;

void GadgetBle::begin()
{
  Serial.println("GadgetBle begin");
  sampleConfigSelector[DataType::T_RH_V3].sampleType = (uint8_t)-1;
  //provider = new DataProvider(lib, DataType::T_RH_V3, true, false, &wifi);
  provider = new DataProvider(lib);
  provider->begin();
  provider->setSampleConfig(DataType::T_RH_CO2_VOC_NOX_PM25);
  //provider->setSampleConfig(DataType::T_RH_CO2_VOC_PM25_HCHO);
  // provider->_historyIntervalMilliSeconds = 60000; //1min
  Serial.print("Sensirion GadgetBle Lib initialized with deviceId = ");
  Serial.println(provider->getDeviceIdString());
}

int x;

void GadgetBle::commitMeasures()
{

  /*
  ++x;
  String s = "SampleHistory: ";
  s += provider->_sampleHistory.numberOfSamplesInHistory();

  Serial.println(s.c_str());

  // provider->writeValueToCurrentSample(x % 50, SignalType::TEMPERATURE_DEGREES_CELSIUS);
  // provider->writeValueToCurrentSample(x % 60, SignalType::RELATIVE_HUMIDITY_PERCENTAGE);
  // provider->writeValueToCurrentSample(x % 70, SignalType::CO2_PARTS_PER_MILLION);
  provider->writeValueToCurrentSample(x % 80, SignalType::VOC_INDEX);
  provider->writeValueToCurrentSample(x % 90, SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER);
  // provider->writeValueToCurrentSample(provider->_sampleHistory.numberOfSamplesInHistory(), SignalType::VOC_INDEX);
  // provider->writeValueToCurrentSample(provider->_historyIntervalMilliSeconds / 1000 , SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER);
  // provider->writeValueToCurrentSample(x % 20, SignalType::HCHO_PARTS_PER_BILLION);
  */


  provider->commitSample();
}

void GadgetBle::handleNetwork()
{
  provider->handleDownload();
}

void GadgetBle::visit(InfoRecord *record) {}
void GadgetBle::visit(ErrorRecord *record) {}
void GadgetBle::visit(MeasureRecord *record)
{
  switch (record->Type)
  {
  case SignalType::TEMPERATURE_DEGREES_CELSIUS:
  case SignalType::RELATIVE_HUMIDITY_PERCENTAGE:
  case SignalType::CO2_PARTS_PER_MILLION:
  case SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER:
  case SignalType::VOC_INDEX:
  //case SignalType::NOX_INDEX:

    provider->writeValueToCurrentSample(record->Value, record->Type);
    break;
  default:
    break;
  }
}

#endif /* enableBLE */