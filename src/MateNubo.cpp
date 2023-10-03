#include "MateNubo.h"

#include "LiquidCrystal_I2C.h"
#include "displayHandler.h"
#include "gatgetBle.h"

void MateNubo::begin(){
    _children.push_back(new displayHandler());
    _children.push_back(new GatgetBle());
    std::for_each(_children.begin(), _children.end(), [](uiInterface* ui){ui->begin();});
}

void MateNubo::commitMeasures(){
    std::for_each(_children.begin(), _children.end(), [](uiInterface* ui){ui->commitMeasures();});
}

void MateNubo::handleNetwork(){
    std::for_each(_children.begin(), _children.end(), [](uiInterface* ui){ui->handleNetwork();});
}

void MateNubo::visit(InfoRecord* record){
    std::for_each(_children.begin(), _children.end(), [record](uiInterface* ui){ui->visit(record);});
}

void MateNubo::visit(ErrorRecord* record){
    std::for_each(_children.begin(), _children.end(), [record](uiInterface* ui){ui->visit(record);});
}

void MateNubo::visit(MeasureRecord* record){
    std::for_each(_children.begin(), _children.end(), [record](uiInterface* ui){ui->visit(record);});
}
