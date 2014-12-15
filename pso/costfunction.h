#ifndef COSTFUNCTION_H
#define COSTFUNCTION_H

#include <cmath>

#include <opencv2/opencv.hpp>

#define COST_INF 9e60

#define PSO_ICP_DEBUG

#ifndef  PSO_ICP_DEBUG
    #define DEMENSION_OF_FREEDOM 26
#else
    #define DEMENSION_OF_FREEDOM 2
    #define PEAKS_NUM 8
#endif

class CostFunction{
public:
#ifdef  PSO_ICP_DEBUG
    static cv::Mat *Fcenters;
    static double peak(const cv::Mat &x, const cv::Mat &center);
#endif
    static double costFunction(const cv::Mat &RGB, const cv::Mat &depth, const cv::Mat &skin, const cv::Mat& p);

};

#endif // COSTFUNCTION_H
