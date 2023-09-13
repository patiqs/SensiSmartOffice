#include "uiInterface.h"
#include "measureRecord.h"

void InfoRecord::accept(uiInterface *ui) { ui->visit(this); }
void ErrorRecord::accept(uiInterface *ui) { ui->visit(this); }
void MeasureRecord::accept(uiInterface *ui) { ui->visit(this); }

volatile int records;

Record::Record(String deviceName) : DeviceName(deviceName){
    ++records;
    // Serial.print("ctor ");
    // Serial.print(DeviceName.c_str());
    // Serial.println(records);
};

Record::~Record() {
    --records;
    // Serial.print("dtor ");
    // Serial.print(DeviceName.c_str());
    // Serial.println(records);
    DeviceName.~String();
}

InfoRecord::~InfoRecord()
{
    Info.~String();
}
ErrorRecord::~ErrorRecord()
{
    Error.~String();
}
MeasureRecord::~MeasureRecord()
{
 
}