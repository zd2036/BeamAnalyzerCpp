#include <vector>
#include <cmath>
#include <numeric>

class BeamAnalyzer {
public:
    static void computeSecondMoments(const std::vector<uint16_t>& img, int w, int h,
                                     double& x_mean, double& y_mean, double& w_x, double& w_y) {
        double sumI = 0, sumX = 0, sumY = 0;
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                double I = img[y * w + x];
                sumI += I;
                sumX += I * x;
                sumY += I * y;
            }
        }
        x_mean = sumX / sumI;
        y_mean = sumY / sumI;

        double sumXX = 0, sumYY = 0;
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                double I = img[y * w + x];
                sumXX += I * (x - x_mean) * (x - x_mean);
                sumYY += I * (y - y_mean) * (y - y_mean);
            }
        }
        w_x = 2 * sqrt(sumXX / sumI);
        w_y = 2 * sqrt(sumYY / sumI);
    }
};
