#pragma once
#include <QObject>
#include <QThread>
#include <QImage>
#include <atomic>

class CameraProvider : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool live READ live NOTIFY liveChanged)
public:
    CameraProvider(QObject* parent=nullptr);
    ~CameraProvider();
    bool live() const { return m_live.load(); }

public slots:
    void start();
    void stop();

signals:
    void frameReady(const QImage &img);
    void liveChanged();

private:
    std::atomic_bool m_live{false};
    QThread m_thread;
    void runLoop();
};
