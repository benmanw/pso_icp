#include "particle.h"

static const double Particle::c1=2.8;
static const double Particle::c2=1.3;
static const double Particle::w=2.0/abs(2-c1-c2-sqrt((c1+c2)*(c1+c2-4)));
static const double Particle::epsilon=1;

static const std::pair<double,double> * Particle::_param_ranges=&(HandStructure::getHandStructure()->param_range);

inline double Particle::map(double v,double old_dbound,double old_ubound,double new_dbound,double new_ubound){
    return (v-old_dbound)*(new_ubound-new_dbound)/(old_ubound-old_dbound)+new_dbound;
}

inline double Particle::random(double ubound,double dbound){
    return map(rand()/(RAND_MAX+1.0),0,1,dbound,ubound);
}

void Particle::reInit(cv::Mat last_best_position){
    velocity=cv::Mat(DEMENSION_OF_FREEDOM,1,CV_64F,cv::Scalar::all(0));
    if(position==last_best_position) return;
    if(random(0,1)<=0.25) return;
    double *p=static_cast<double*>(position.data);
    double *q=static_cast<double*>(last_best_position.data);
    for(int i=0;i<DEMENSION_OF_FREEDOM;i++){
        *p=random(std::max(param_ranges[i].first,*q-epsilon),std::min(param_ranges[i].second,*q+epsilon));
        p++; q++;
    }
    hist_best_cost=COST_INF;
}

void Particle::checkBound(){
    double *p=static_cast<double*>(position.data);
    for(int i=0;i<DEMENSION_OF_FREEDOM;i++){
        if(*p>_param_ranges[i].second) *p=_param_ranges[i].second;
        if(*p<_param_ranges[i].first) *p=_param_ranges[i].first;
        p++;
    }
}

Particle::Particle(){
    velocity=cv::Mat(DEMENSION_OF_FREEDOM,1,CV_64F,cv::Scalar::all(0));
    position.create(DEMENSION_OF_FREEDOM,1,CV_64F);
    double *p=static_cast<double*>(position.data);
    for(int i=0;i<DEMENSION_OF_FREEDOM;i++){
        *p=random(_param_ranges[i].first,_param_ranges[i].second);
        p++;
    }
    hist_best_cost=COST_INF;
}

void Particle::calcCost(const cv::Mat &RGB, const cv::Mat &depth, const cv::Mat &skin){
    cost=costFunction(RGB,depth,skin,position);
    if(cost<hist_best_cost){
        hist_best_position=position.clone();
        hist_best_cost=cost;
    }
}

void Particle::update(const cv::Mat& global_best_position,const cv::Mat &RGB, const cv::Mat &depth, const cv::Mat &skin){
    position=position+velocity;
    checkBound();
    calcCost(RGB,depth,skin);
    velocity=(velocity+(global_best_position-position)*c1*random(0,1)+(hist_best_position-position)*c2*random(0,1))*w;
}
