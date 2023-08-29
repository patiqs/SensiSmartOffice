#ifdef BLE
#include "gatgetBle.h"
#include "Sensirion_Gadget_BLE.h"

NimBLELibraryWrapper lib;
DataProvider provider(lib, DataType::T_RH_CO2_VOC_PM25_HCHO_V2);

void GatgetBle::begin()
{
  provider.begin();
  Serial.print("Sensirion GadgetBle Lib initialized with deviceId = ");
  Serial.println(provider.getDeviceIdString());
}

void GatgetBle::pushMeasure(MeasureRecord measure)
{
  provider.writeValueToCurrentSample(5.0, SignalType::TEMPERATURE_DEGREES_CELSIUS);
  provider.writeValueToCurrentSample(5.0, SignalType::HCHO_PARTS_PER_BILLION);
  provider.commitSample();
}

void GatgetBle::pushMeasures(std::vector<MeasureRecord> measures)
{
  std::for_each(measures.begin(), measures.end(), [](MeasureRecord m)
                { provider.writeValueToCurrentSample(m.fVal, m.Type); });
  provider.commitSample();
}

void GatgetBle::commitMeasures()
{
  provider.handleDownload();
}

#endif /* BLE */
