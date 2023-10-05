#include "compoundUi.h"

#ifdef enableDisplay
#include "displayHandler.h"
#endif
#ifdef enableWEB
#include "Web.h"
#endif 
#ifdef enableBLE
#include "gadgetBle.h"
#endif 



void CompoundUi::begin(){
    #ifdef enableBLE
        _children.push_back(new GadgetBle());
    #endif
    #ifdef enableWEB
        _children.push_back(new Web());
    #endif
    #ifdef enableDisplay
        _children.push_back(new displayHandler()); 
    #endif
    std::for_each(_children.begin(), _children.end(), [](uiInterface* ui){ui->begin();});
}

void CompoundUi::commitMeasures(){
    std::for_each(_children.begin(), _children.end(), [](uiInterface* ui){ui->commitMeasures();});
}

void CompoundUi::handleNetwork(){
    std::for_each(_children.begin(), _children.end(), [](uiInterface* ui){ui->handleNetwork();});
}

void CompoundUi::visit(InfoRecord* record){
    std::for_each(_children.begin(), _children.end(), [record](uiInterface* ui){ui->visit(record);});
}

void CompoundUi::visit(ErrorRecord* record){
    std::for_each(_children.begin(), _children.end(), [record](uiInterface* ui){ui->visit(record);});
}

void CompoundUi::visit(MeasureRecord* record){
    std::for_each(_children.begin(), _children.end(), [record](uiInterface* ui){ui->visit(record);});
}
