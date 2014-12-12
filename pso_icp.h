#ifndef PSO_ICP_H
#define PSO_ICP_H

#include <opencv2/opencv.hpp>

#include "particle.h"

class PSO_ICP
{
    bool reInit_flag;
    const int particle_num,kmeans_k,generation,kmeans_generation;
    std::pair<double, cv::Mat> *swarm_best_position;
    cv::Mat last_best_position;
    Particle *particles;
    int *swarm_id_of_particles;
    double best_cost;
public:
    PSO_ICP();
    cv::Mat solve(const cv::Mat &RGB, const cv::Mat &depth, const cv::Mat &skin);
    void kmeans();
    ~PSO_ICP();
};

#endif // PSO_ICP_H
