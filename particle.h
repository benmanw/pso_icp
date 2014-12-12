#ifndef PARTICLE_H
#define PARTICLE_H

#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <cmath>

#include "handstructure.h"

class Particle
{
    cv::Mat velocity;
public:
    cv::Mat position, hist_best_position;
    double cost, hist_best_cost;

private:
    static const double w,c1,c2,epsilon;
    static const std::pair<double,double> *_param_ranges;

    inline double map(double v,double old_dbound,double old_ubound,double new_dbound,double new_ubound);

    inline double random(double ubound,double dbound);

    void checkBound();

    void calcCost(const cv::Mat &RGB, const cv::Mat &depth, const cv::Mat &skin);

    void reInit(cv::Mat last_best_position);

public:
    Particle();
    void update(const cv::Mat& global_best_position,const cv::Mat &RGB, const cv::Mat &depth, const cv::Mat &skin);
};

#endif // PARTICLE_H
