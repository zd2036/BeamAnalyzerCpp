#include "core/BeamAnalyzer.h"
#include <cmath>

BeamMetrics BeamAnalyzer::analyze(const cv::Mat &image, const cv::Mat &background) {
    cv::Mat img;
    if (image.type() != CV_64F) image.convertTo(img, CV_64F);
    else img = image.clone();
    if (!background.empty()) {
        cv::Mat bg;
        if (background.type() != CV_64F) background.convertTo(bg, CV_64F);
        else bg = background;
        img -= bg;
    }
    cv::threshold(img, img, 0.0, 0.0, cv::THRESH_TOZERO);

    BeamMetrics m;
    m.totalPower = cv::sum(img)[0];
    if (m.totalPower <= 0) return m;

    double sx = 0, sy = 0;
    for (int y = 0; y < img.rows; ++y) {
        const double* row = img.ptr<double>(y);
        for (int x = 0; x < img.cols; ++x) {
            double I = row[x];
            sx += I * x;
            sy += I * y;
        }
    }
    m.cx = sx / m.totalPower;
    m.cy = sy / m.totalPower;

    double mxx = 0, myy = 0;
    for (int y = 0; y < img.rows; ++y) {
        const double* row = img.ptr<double>(y);
        double dy = y - m.cy;
        for (int x = 0; x < img.cols; ++x) {
            double I = row[x];
            double dx = x - m.cx;
            mxx += I * dx * dx;
            myy += I * dy * dy;
        }
    }
    mxx /= m.totalPower; myy /= m.totalPower;
    m.sigmaX = std::sqrt(mxx);
    m.sigmaY = std::sqrt(myy);
    m.D4sigmaX = 4.0 * m.sigmaX;
    m.D4sigmaY = 4.0 * m.sigmaY;
    return m;
}
