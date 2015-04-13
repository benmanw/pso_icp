#ifndef COSTFUNCTIONDEMO_H
#define COSTFUNCTIONDEMO_H

#include <cmath>
#include <stdlib.h>

#include "icostfunction.h"
#include "particle.h"

class CostFunctionDemo: public ICostFunction {

public:
    cv::Mat *Fcenters;

    CostFunctionDemo();
    ~CostFunctionDemo();

    double peak(const cv::Mat &x, const cv::Mat &center);
    double costFunction(const cv::Mat& position);
};

#endif // COSTFUNCTIONDEMO_H
