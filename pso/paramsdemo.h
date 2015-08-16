#ifndef PARAMSDEMO_h
#define PARAMSDEMO_h

#include "IParams.h"

class ParamsDemo : public IParams {
public:
	static std::vector<std::pair<double, double> > paramRange;
	const static int dimension_of_freedom;

	ParamsDemo() : IParams() {};
	ParamsDemo(cv::Mat m) : IParams(m) {};
	ParamsDemo(const std::vector<double> &v) : IParams(v) {};
};

#endif  // PARAMSDEMO_h