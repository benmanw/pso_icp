#ifndef PARTICLE_H
#define PARTICLE_H

#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <cmath>

#include "icostfunction.h"

#define COST_INF (9e60)

template <typename ParamsType>
class Particle {
    static const double c1,c2,epsilon,w;
    cv::Mat velocity;
	ICostFunction<ParamsType> *_costFunc;

public:
    cv::Mat position, hist_best_position;
    double cost, hist_best_cost;

    static double map(double v,double old_dbound,double old_ubound,double new_dbound,double new_ubound);

    static inline double random(double ubound,double dbound);

private:

    bool equal(const cv::Mat &a,const cv::Mat &b);
    void checkBound();

public:
	Particle(ICostFunction<ParamsType> *costFunc);
    void calcCost();
    void reInit(cv::Mat last_best_position);
    void update(const cv::Mat& global_best_position);
};


// the config of the algorithm --------------

template <typename ParamsType>
const double Particle<ParamsType>::c1 = 2.8,
	Particle<ParamsType>::c2 = 1.3,
	Particle<ParamsType>::epsilon = 1,
	Particle<ParamsType>::w = 2.0 / abs(2 - c1 - c2 - sqrt((c1 + c2)*(c1 + c2 - 4)));

// config end -------------------------------

template <typename ParamsType>
double Particle<ParamsType>::map(double v, double old_dbound, double old_ubound, double new_dbound, double new_ubound){
	return (v - old_dbound)*(new_ubound - new_dbound) / (old_ubound - old_dbound) + new_dbound;
}

template <typename ParamsType>
inline double Particle<ParamsType>::random(double ubound, double dbound){
	return map(rand() / (RAND_MAX + 1.0), 0, 1, dbound, ubound);
}

template <typename ParamsType>
bool Particle<ParamsType>::equal(const cv::Mat &a, const cv::Mat &b){
	const double *p = a.ptr<double>();
	const double *q = b.ptr<double>();
	for (int i = 0; i<ParamsType::dimension_of_freedom; i++, p++, q++){
		if (*p != *q) return false;
	}
	return true;
}

template <typename ParamsType>
void Particle<ParamsType>::reInit(cv::Mat last_best_position){
	velocity = cv::Mat(ParamsType::dimension_of_freedom, 1, CV_64F, cv::Scalar::all(0)); // reset velocity
	if (equal(position, last_best_position)) return;  // copy the best particle to next frame
	if (random(0, 1) <= 0.25) return; // copy 1/4 particles to next frame
	double *p = position.ptr<double>();
	double *q = last_best_position.ptr<double>();
	for (int i = 0; i<ParamsType::dimension_of_freedom; i++){
		*p = random(std::max(ParamsType::paramRange[i].first, *q - epsilon), std::min(ParamsType::paramRange[i].second, *q + epsilon));
		p++; q++;
	}
	hist_best_cost = COST_INF;
}

template <typename ParamsType>
void Particle<ParamsType>::checkBound(){
	double *p = position.ptr<double>();
	for (int i = 0; i<ParamsType::dimension_of_freedom; i++){
		if (*p > ParamsType::paramRange[i].second) *p = ParamsType::paramRange[i].second;
		if (*p < ParamsType::paramRange[i].first) *p = ParamsType::paramRange[i].first;
		p++;
	}
}

template <typename ParamsType>
Particle<ParamsType>::Particle(ICostFunction<ParamsType> *costFunc) :
_costFunc(costFunc)
{
	velocity = cv::Mat(ParamsType::dimension_of_freedom, 1, CV_64F, cv::Scalar::all(0));
	position.create(ParamsType::dimension_of_freedom, 1, CV_64F);
	double *p = position.ptr<double>();
	for (int i = 0; i<ParamsType::dimension_of_freedom; i++){
		*p = random(ParamsType::paramRange[i].first, ParamsType::paramRange[i].second);
		p++;
	}
	hist_best_cost = COST_INF;
}

template <typename ParamsType>
void Particle<ParamsType>::calcCost(){
	ParamsType tmp(position);
	cost = _costFunc->costFunction(tmp);
	if (cost<hist_best_cost){
		hist_best_position = position.clone();
		hist_best_cost = cost;
	}
}

template <typename ParamsType>
void Particle<ParamsType>::update(const cv::Mat& global_best_position){
	position = position + velocity;
	checkBound();
	calcCost();
	velocity = (velocity + (global_best_position - position)*c1*random(0, 1) + (hist_best_position - position)*c2*random(0, 1))*w;
}


#endif // PARTICLE_H
