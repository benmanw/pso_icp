#ifndef ICOSTFUNCTION_H
#define ICOSTFUNCTION_H

#define COST_INF 9e60

#include <opencv2/opencv.hpp>

class ICostFunction {
public:
    virtual double costFunction(const cv::Mat& position) {
        throw "ICostFunction::costFunction() Called - You must implement this method in child class.";
    }
};

#endif // ICOSTFUNCTION_H
