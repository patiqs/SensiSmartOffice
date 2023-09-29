#include "uiInterface.h"
#include "record.h"

void InfoRecord::accept(uiInterface *ui) { ui->visit(this); }
void ErrorRecord::accept(uiInterface *ui) { ui->visit(this); }
void MeasureRecord::accept(uiInterface *ui) { ui->visit(this); }

volatile int records;

Record::Record(String deviceName) : DeviceName(deviceName){
};

Record::~Record() {
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
