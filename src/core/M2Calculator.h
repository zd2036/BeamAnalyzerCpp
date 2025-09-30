#pragma once
#include <vector>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

struct M2Result {
    double M2 = NAN;
    double W0 = NAN;
    double z0 = NAN;
    double fitA = NAN, fitB = NAN;
    double rss = NAN;
};
class M2Calculator {
public:
    static M2Result computeM2(const std::vector<double>& z, const std::vector<double>& D4sigma, double lambda);
};
