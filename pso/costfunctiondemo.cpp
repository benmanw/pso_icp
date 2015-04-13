#include "costfunctiondemo.h"

static const int PEAKS_NUM = 8;

// linear transform function
static inline double map(double v,double old_dbound,double old_ubound,double new_dbound,double new_ubound){
    return (v-old_dbound)*(new_ubound-new_dbound)/(old_ubound-old_dbound)+new_dbound;
}

static inline double random(double ubound, double dbound){
    return map(rand()/(RAND_MAX+1.0),0,1,dbound,ubound);
}

CostFunctionDemo::CostFunctionDemo() {
    // some code to randomize the params of the made-up cost function
    Fcenters = new cv::Mat[PEAKS_NUM];
    for(int i=0; i<PEAKS_NUM; i++){
        Fcenters[i] = cv::Mat(DIMENSION_OF_FREEDOM, 1, CV_64F);
        double *p = Fcenters[i].ptr<double>();
        for(int j=0; j<DIMENSION_OF_FREEDOM; j++, p++){
            *p = random(0, Particle::param_ranges[j][1]);
        }
    }
}

CostFunctionDemo::~CostFunctionDemo() {
    delete [] Fcenters;
}

double CostFunctionDemo::peak(const cv::Mat &x, const cv::Mat &center){
    cv::Mat tmp = x-center;
    return -exp(-tmp.dot(tmp)*0.32);
}

// a made-up cost function demo
double CostFunctionDemo::costFunction(const cv::Mat &position){
    double cost = 0;
    for(int i=0 ;i<PEAKS_NUM; i++){
        cost += peak(position,Fcenters[i]);
    }
    return cost*(6+sin(*(position.ptr<double>())));
}
