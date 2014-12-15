#include "costfunction.h"

#ifdef PSO_ICP_DEBUG

cv::Mat * CostFunction::Fcenters=new cv::Mat[PEAKS_NUM];

double CostFunction::peak(const cv::Mat &x, const cv::Mat &center){
    cv::Mat tmp=x-center;
    return -exp(-tmp.dot(tmp)*0.32);
}

#endif

double CostFunction::costFunction(const cv::Mat &RGB, const cv::Mat &depth, const cv::Mat &skin, const cv::Mat& p){
#ifndef PSO_ICP_DEBUG
    // TODO: add cost function
    return 0;
#else
    double cost=0;
    for(int i=0;i<PEAKS_NUM;i++){
        cost+=peak(p,Fcenters[i]);
    }
    return cost*(6+sin(*(p.ptr<double>())));
#endif
}
