#pragma once
#include <QObject>

struct BeamDataStruct {
    double cx=0, cy=0, D4x=0, D4y=0;
};

class BeamData : public QObject {
    Q_OBJECT
    Q_PROPERTY(double cx READ cx NOTIFY changed)
    Q_PROPERTY(double cy READ cy NOTIFY changed)
    Q_PROPERTY(double D4x READ D4x NOTIFY changed)
    Q_PROPERTY(double D4y READ D4y NOTIFY changed)
public:
    BeamData(QObject* parent=nullptr): QObject(parent) {}
    double cx() const { return m.cx; }
    double cy() const { return m.cy; }
    double D4x() const { return m.D4x; }
    double D4y() const { return m.D4y; }
    void setData(const BeamDataStruct &d) {
        m = d;
        emit changed();
    }
signals:
    void changed();
private:
    BeamDataStruct m;
};
