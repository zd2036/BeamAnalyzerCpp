#pragma once
#include <opencv2/opencv.hpp>

struct BeamMetrics {
    double totalPower = 0.0;
    double cx = 0.0, cy = 0.0;
    double sigmaX = 0.0, sigmaY = 0.0;
    double D4sigmaX = 0.0, D4sigmaY = 0.0;
};

class BeamAnalyzer {
public:
    static BeamMetrics analyze(const cv::Mat &image, const cv::Mat &background = cv::Mat());
};
