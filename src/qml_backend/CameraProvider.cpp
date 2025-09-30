#include "qml_backend/CameraProvider.h"
#include <opencv2/opencv.hpp>
#include <QTimer>
#include <QDebug>
#include <chrono>
#include <thread>
#include <cmath>

CameraProvider::CameraProvider(QObject* parent): QObject(parent) {
}

CameraProvider::~CameraProvider() {
    stop();
}

void CameraProvider::start() {
    if (m_live.load()) return;
    m_live = true;
    emit liveChanged();
    // run in separate std::thread to avoid QObject move complexities
    std::thread([this]() { runLoop(); }).detach();
}

void CameraProvider::stop() {
    m_live = false;
    emit liveChanged();
}

static QImage cvMatToQImage(const cv::Mat &mat) {
    if (mat.type() == CV_8UC1) {
        QImage img(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
        return img.copy();
    } else if (mat.type() == CV_64F) {
        cv::Mat tmp; mat.convertTo(tmp, CV_8U);
        QImage img(tmp.data, tmp.cols, tmp.rows, tmp.step, QImage::Format_Grayscale8);
        return img.copy();
    }
    return QImage();
}

static cv::Mat generateGaussianImage(int w, int h, double cx, double cy, double sigma) {
    cv::Mat img(h, w, CV_64F, cv::Scalar(0));
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double dx = x - cx; double dy = y - cy;
            double val = std::exp(-(dx*dx+dy*dy)/(2*sigma*sigma));
            img.at<double>(y,x) = val*255.0;
        }
    }
    return img;
}

void CameraProvider::runLoop() {
    int w = 640, h = 480;
    double cx = w/2.0, cy = h/2.0, sigma = 40.0;
    double t = 0.0;
    while (m_live.load()) {
        // animate center
        double ox = 60.0 * std::sin(t*0.5);
        double oy = 30.0 * std::cos(t*0.7);
        cv::Mat img = generateGaussianImage(w,h, cx+ox, cy+oy, sigma);
        QImage qimg = cvMatToQImage(img);
        emit frameReady(qimg);
        t += 0.1;
        std::this_thread::sleep_for(std::chrono::milliseconds(40)); // ~25 FPS
    }
}
