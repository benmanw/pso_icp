#include "particle.h"

// the config of the algorithm --------------

const double Particle::c1=2.8,
             Particle::c2=1.3,
             Particle::epsilon=1,
             Particle::w=2.0/abs(2-c1-c2-sqrt((c1+c2)*(c1+c2-4)));

const double Particle::param_ranges[DIMENSION_OF_FREEDOM][2] = {
    {0, 10}, {0, 10}
};  // the bound of each dimension

// config end -------------------------------

double Particle::map(double v,double old_dbound,double old_ubound,double new_dbound,double new_ubound){
    return (v-old_dbound)*(new_ubound-new_dbound)/(old_ubound-old_dbound)+new_dbound;
}

inline double Particle::random(double ubound,double dbound){
    return map(rand()/(RAND_MAX+1.0),0,1,dbound,ubound);
}

bool Particle::equal(const cv::Mat &a,const cv::Mat &b){
    const double *p=a.ptr<double>();
    const double *q=b.ptr<double>();
    for(int i=0; i<DIMENSION_OF_FREEDOM; i++,p++,q++){
        if(*p!=*q) return false;
    }
    return true;
}

void Particle::reInit(cv::Mat last_best_position){
    velocity=cv::Mat(DIMENSION_OF_FREEDOM,1,CV_64F,cv::Scalar::all(0)); // reset velocity
    if(equal(position,last_best_position)) return;  // copy the best particle to next frame
    if(random(0,1)<=0.25) return; // copy 1/4 particles to next frame
    double *p = position.ptr<double>();
    double *q = last_best_position.ptr<double>();
    for(int i=0; i<DIMENSION_OF_FREEDOM; i++){
        *p = random(std::max(param_ranges[i][0],*q-epsilon),std::min(param_ranges[i][1],*q+epsilon));
        p++; q++;
    }
    hist_best_cost=COST_INF;
}

void Particle::checkBound(){
    double *p = position.ptr<double>();
    for(int i=0; i<DIMENSION_OF_FREEDOM; i++){
        if(*p > param_ranges[i][1]) *p = param_ranges[i][1];
        if(*p < param_ranges[i][0]) *p = param_ranges[i][0];
        p++;
    }
}

Particle::Particle(ICostFunction *costFunc):
    _costFunc(costFunc)
{
    velocity=cv::Mat(DIMENSION_OF_FREEDOM,1,CV_64F,cv::Scalar::all(0));
    position.create(DIMENSION_OF_FREEDOM,1,CV_64F);
    double *p = position.ptr<double>();
    for(int i=0; i<DIMENSION_OF_FREEDOM; i++){
        *p = random(param_ranges[i][0], param_ranges[i][1]);
        p++;
    }
    hist_best_cost=COST_INF;
}

void Particle::calcCost(){
    cost = _costFunc->costFunction(position);
    if(cost<hist_best_cost){
        hist_best_position=position.clone();
        hist_best_cost=cost;
    }
}

void Particle::update(const cv::Mat& global_best_position){
    position=position+velocity;
    checkBound();
    calcCost();
    velocity=(velocity+(global_best_position-position)*c1*random(0,1)+(hist_best_position-position)*c2*random(0,1))*w;
}
