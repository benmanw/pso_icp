#include "pso_icp.h"

PSO_ICP::PSO_ICP():
    particle_num(64),
    kmeans_k(4),
    kmeans_generation(10),
    generation(30)
{
    reInit_flag=false;
    particles=new particles[particle_num];
    swarm_best_position=new std::pair<double, cv::Mat> [kmeans_k];
    swarm_id_of_particles=new int [particle_num];
}

PSO_ICP::~PSO_ICP()
{
    delete [] particles;
    delete [] swarm_best_position;
    delete [] swarm_id_of_particles;
}

void PSO_ICP::kmeans(){

}

cv::Mat PSO_ICP::solve(const cv::Mat &RGB, const cv::Mat &depth, const cv::Mat &skin){

    if(reInit_flag){
        for(int i=0;i<particle_num;i++){
            particles[i].reInit(last_best_position);
        }
    }else{
        reInit_flag=true;
    }

    for(int j=0;j<particle_num;j++){
        particles[j].calcCost(RGB,depth,skin);
    }

    for(int i=0;i<generation;i++){

        kmeans();

        for(int j=0;j<kmeans_k;j++){
            swarm_best_position[j].first=COST_INF;
        }

        for(int j=0;j<particle_num;j++){
            double &best_cost=swarm_best_position[swarm_id_of_particles[j]].first;
            if(best_cost>particles[j].cost){
                best_cost=particles[j].cost;
                swarm_best_position[swarm_id_of_particles[j]].second=particles[j].position.clone();
            }
        }

        for(int j=0;j<particle_num;j++){
            cv::Mat &swarm_global_best_position=swarm_best_position[swarm_id_of_particles[j]].second;
            particles[j].update(swarm_global_best_position,RGB,depth,skin);
        }

    }

    best_cost=COST_INF;
    for(int j=0;j<particle_num;j++){
        if(best_cost>particles[j].cost){
            best_cost=particles[j].cost;
            last_best_position=particles[j].position.clone();
        }
    }

    return last_best_position;

}
