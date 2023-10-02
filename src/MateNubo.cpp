#if defined(MateNubo)
#include "gatgetBle.h"
#include "Sensirion_GatgetBle.h"
#include "LiquidCrystal_I2C.h"
//#include "WifiMultiLibraryWrapper.h"

NimBLELibraryWrapper lib;
//WifiMultiLibraryWrapper wifi;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void MateNubo::begin()
{
  sampleConfigSelector[DataType::T_RH_V3].sampleType = (uint8_t)-1;
  //provider = new DataProvider(lib, DataType::T_RH_V3, true, false, &wifi);
  provider = new DataProvider(lib);
  provider->begin();
  provider->setSampleConfig(DataType::T_RH_CO2_VOC_NOX_PM25);
  lcd.init();
  lcd.backlight();
  // provider->_historyIntervalMilliSeconds = 60000; //1min
  Serial.print("Sensirion GadgetBle Lib initialized with deviceId = ");
  Serial.println(provider->getDeviceIdString());
}


int x;

void MateNubo::commitMeasures()
{
  provider->commitSample();
}

void MateNubo::handleNetwork()
{
  provider->handleDownload();
}

void MateNubo::visit(InfoRecord *record) {}
void MateNubo::visit(ErrorRecord *record) {}
void MateNubo::visit(MeasureRecord *record)
{
  switch (record->Type)
  {
  case SignalType::RELATIVE_HUMIDITY_PERCENTAGE:
  case SignalType::TEMPERATURE_DEGREES_CELSIUS:
  case SignalType::VOC_INDEX:
  case SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER:
  case SignalType::CO2_PARTS_PER_MILLION:
    provider->writeValueToCurrentSample(record->Value, record->Type);
    break;
  default:
    break;
  }
}

#endif /* BLE */
