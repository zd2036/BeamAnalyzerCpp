#pragma once
#include <QObject>
#include "qml_backend/BeamData.h"
#include <QImage>

class AnalyzerBridge : public QObject {
    Q_OBJECT
    Q_PROPERTY(BeamData* beamData READ beamData CONSTANT)
public:
    AnalyzerBridge(QObject* parent=nullptr);
    BeamData* beamData() { return &m_data; }

public slots:
    void analyzeImage(const QImage &img);

signals:
    void analysisDone();

private:
    BeamData m_data;
};
