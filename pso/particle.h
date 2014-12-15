#ifndef PARTICLE_H
#define PARTICLE_H

#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <cmath>

#include "handstructure.h"

class Particle
{
    static const double c1,c2,epsilon,w;
    cv::Mat velocity;

public:
    cv::Mat position, hist_best_position;
    double cost, hist_best_cost;

    static const std::pair<double,double> *param_ranges;

    static inline double map(double v,double old_dbound,double old_ubound,double new_dbound,double new_ubound);

    static inline double random(double ubound,double dbound);

private:

    bool equal(const cv::Mat &a,const cv::Mat &b);

    void checkBound();

public:
    Particle();
    void calcCost(const cv::Mat &RGB, const cv::Mat &depth, const cv::Mat &skin);
    void reInit(cv::Mat last_best_position);
    void update(const cv::Mat& global_best_position,const cv::Mat &RGB, const cv::Mat &depth, const cv::Mat &skin);
};

#endif // PARTICLE_H
