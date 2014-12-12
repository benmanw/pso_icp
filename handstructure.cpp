#include "handstructure.h"

#define PI 3.1415927

HandStructure::HandStructure()
{
    for(int i=0;i<DEMENSION_OF_FREEDOM;i++){
        param_range[i].first=-PI;
        param_range[i].second=PI;
    }

    // TODO: set up the properties
}

const HandStructure * HandStructure::getHandStructure(){
    if(hand_structure_pointer==NULL){
        hand_structure_pointer=new HandStructure();
    }
    return hand_structure_pointer;
}

HandStructure * HandStructure::hand_structure_pointer=NULL;
