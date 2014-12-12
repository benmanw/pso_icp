#ifndef HANDSTRUCTURE_H
#define HANDSTRUCTURE_H

#include <vector>

#include <opencv2/opencv.hpp>

#include "costfunction.h"

#define NUMBER_OF_PARTS

class HandStructure
{
    static HandStructure *hand_structure_pointer;
    HandStructure();
public:
    static std::vector<std::vector<int>> part_components;
    static int part_parent[NUMBER_OF_PARTS];
    static int param_part[DEMENSION_OF_FREEDOM];
    static std::pair<double,double> param_range[DEMENSION_OF_FREEDOM];
    static const HandStructure *getHandStructure();
};

#endif // HANDSTRUCTURE_H
