#ifndef PSO_ICP_H
#define PSO_ICP_H

#include <vector>

#include <opencv2/opencv.hpp>

#include "particle.h"

class PSO_ICP
{
    bool reInit_flag;
    const int particle_num,generation,kmeans_generation,kmeans_k;
    std::pair<double, cv::Mat> *swarm_best_position;
    cv::Mat last_best_position;
    std::vector<Particle> particles;
    int *swarm_id_of_particles;
    double best_cost;
    cv::Mat *kmeans_centroid;

    void kmeans();
        void kmeans_set_centroid();
        void kmeans_set_swarm_id();
        void kmeans_update_centroid();

public:

    PSO_ICP(ICostFunction *costFunc);

    cv::Mat solve();

    ~PSO_ICP();
};

#endif // PSO_ICP_H
