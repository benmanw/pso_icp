/*Copyright (c) 2014, School of Computer Science, Fudan University*/
#ifndef DEBUGTIMER_H
#define DEBUGTIMER_H

//#include "FduVideo_lib.hpp"
#include <sys/time.h>
#include <iostream>
#include <cmath>

class Timer{
    timeval t1, t2;
    double result;
public:
    Timer(){
        gettimeofday(&t1, NULL);
    }
    void out(const std::string func=""){
        gettimeofday(&t2, NULL);
        result=(t2.tv_sec-t1.tv_sec)*1e6+(t2.tv_usec-t1.tv_usec);
        result/=1e3;
        std::cout<<"["<<func<<"] Time: "<<round(result)<<std::endl;
        gettimeofday(&t1, NULL);
    }
};

#endif // DEBUGTIMER_H
