#ifndef COSTFUNCTION_H
#define COSTFUNCTION_H

#include <opencv2/opencv.hpp>

#define COST_INF 9e60

#define DEMENSION_OF_FREEDOM 26

double costFunction(const cv::Mat &RGB, const cv::Mat &depth, const cv::Mat &skin, const cv::Mat& p);

#endif // COSTFUNCTION_H
