#include "qml_backend/AnalyzerBridge.h"
#include <opencv2/opencv.hpp>
#include "core/BeamAnalyzer.h"

AnalyzerBridge::AnalyzerBridge(QObject* parent): QObject(parent) {
}

static cv::Mat QImageToCvMat(const QImage &inImage) {
    QImage img = inImage.convertToFormat(QImage::Format_Grayscale8);
    cv::Mat mat(img.height(), img.width(), CV_8UC1, (void*)img.constBits(), img.bytesPerLine());
    cv::Mat d;
    mat.convertTo(d, CV_64F);
    return d.clone();
}

void AnalyzerBridge::analyzeImage(const QImage &img) {
    cv::Mat mat = QImageToCvMat(img);
    BeamMetrics m = BeamAnalyzer::analyze(mat);
    BeamDataStruct b;
    b.cx = m.cx; b.cy = m.cy; b.D4x = m.D4sigmaX; b.D4y = m.D4sigmaY;
    m_data.setData(b);
    emit analysisDone();
}
