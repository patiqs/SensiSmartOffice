#include "uiInterface.h"
#include "measureRecord.h"

void InfoRecord::accept(uiInterface *ui) { ui->visit(this); }
void ErrorRecord::accept(uiInterface *ui) { ui->visit(this); }
void MeasureRecord::accept(uiInterface *ui) { ui->visit(this); }
