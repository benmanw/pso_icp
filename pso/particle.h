#ifndef PARTICLE_H
#define PARTICLE_H

#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <cmath>

#include "icostfunction.h"

const int DIMENSION_OF_FREEDOM = 2;

class Particle {
    static const double c1,c2,epsilon,w;
    cv::Mat velocity;
    ICostFunction *_costFunc;

public:
    cv::Mat position, hist_best_position;
    double cost, hist_best_cost;

    static const double param_ranges[DIMENSION_OF_FREEDOM][2];

    static double map(double v,double old_dbound,double old_ubound,double new_dbound,double new_ubound);

    static inline double random(double ubound,double dbound);

private:

    bool equal(const cv::Mat &a,const cv::Mat &b);
    void checkBound();

public:
    Particle(ICostFunction *costFunc);
    void calcCost();
    void reInit(cv::Mat last_best_position);
    void update(const cv::Mat& global_best_position);
};

#endif // PARTICLE_H
