#ifndef COSTFUNCTIONDEMO_H
#define COSTFUNCTIONDEMO_H

#include <cmath>
#include <stdlib.h>

#include "icostfunction.h"
#include "paramsdemo.h"
#include "particle.h"

class CostFunctionDemo: public ICostFunction<ParamsDemo> {
	double peak(const cv::Mat &x, const cv::Mat &center);
public:
    cv::Mat *Fcenters;

    CostFunctionDemo();
    ~CostFunctionDemo();

	virtual double costFunction(const ParamsDemo&);
};

#endif // COSTFUNCTIONDEMO_H
