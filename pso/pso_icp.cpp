#include "pso_icp.h"

PSO_ICP::PSO_ICP():
    particle_num(64),
    kmeans_k(4),
    kmeans_generation(10),
    generation(30)
{
    reInit_flag=false;
    particles=new Particle[particle_num];
    swarm_best_position=new std::pair<double, cv::Mat> [kmeans_k];
    kmeans_centroid=new cv::Mat [kmeans_k];
    swarm_id_of_particles=new int [particle_num];
}

PSO_ICP::~PSO_ICP()
{
    delete [] particles;
    delete [] swarm_best_position;
    delete [] swarm_id_of_particles;
    delete [] kmeans_centroid;
}

void PSO_ICP::kmeans_set_swarm_id(){
    for(int j=0;j<particle_num;j++){
        double dist=COST_INF;
        for(int i=0;i<kmeans_k;i++){
            cv::Mat diff=particles[j].position-kmeans_centroid[i];
            double tmp=diff.dot(diff);
            if(tmp<dist){
                dist=tmp;
                swarm_id_of_particles[j]=i;
            }
        }
    }
}

void PSO_ICP::kmeans_update_centroid(){
    cv::Mat *new_kmeans_centroid=new cv::Mat[kmeans_k];
    int *counter=new int[kmeans_k];
    for(int i=0;i<kmeans_k;++i){
        counter[i]=0;
        new_kmeans_centroid[i]=cv::Mat(DEMENSION_OF_FREEDOM,1,CV_64F,cv::Scalar::all(0));
    }
    for(int j=0;j<particle_num;j++){
        counter[swarm_id_of_particles[j]]++;
        new_kmeans_centroid[swarm_id_of_particles[j]]=new_kmeans_centroid[swarm_id_of_particles[j]]+particles[j].position;
    }
    for(int i=0;i<kmeans_k;++i){
        if(counter[i]!=0)
            new_kmeans_centroid[i]=new_kmeans_centroid[i]/(1.0*counter[i]);
    }
    delete [] kmeans_centroid;
    kmeans_centroid=new_kmeans_centroid;
    delete [] counter;
}

void PSO_ICP::kmeans_set_centroid(){
    int *p=new int [particle_num];
    for(int i=0;i<particle_num;i++)
        p[i]=i;
    for(int i=0;i<kmeans_k;i++){
        int pick=rand()%(particle_num-i);
        kmeans_centroid[i]=particles[p[pick]].position;
        p[pick]=p[particle_num-i-1];
    }
    delete [] p;
}

void PSO_ICP::kmeans(){
    kmeans_set_centroid();
    for(int i=0;i<kmeans_generation;i++){
        kmeans_set_swarm_id();
        if(i!=kmeans_generation-1)
            kmeans_update_centroid();
    }
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

        // TODO: add AICP Algorithm here

        kmeans();

        // then find the best particle in each swarm/cluster

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

        // update the stat of particles

        for(int j=0;j<particle_num;j++){
            cv::Mat &swarm_global_best_position=swarm_best_position[swarm_id_of_particles[j]].second;
            particles[j].update(swarm_global_best_position,RGB,depth,skin);
        }

    }

    // find the real global best particle in history

    best_cost=COST_INF;
    for(int j=0;j<particle_num;j++){
        if(best_cost>particles[j].hist_best_cost){
            best_cost=particles[j].hist_best_cost;
            last_best_position=particles[j].hist_best_position.clone();
        }
    }

    return last_best_position;

}
