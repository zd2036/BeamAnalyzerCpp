#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "qml_backend/CameraProvider.h"
#include "qml_backend/AnalyzerBridge.h"
#include <QQuickStyle>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");

    qmlRegisterType<CameraProvider>("Beam.Camera", 1, 0, "CameraProvider");
    qmlRegisterType<AnalyzerBridge>("Beam.Analyzer", 1, 0, "AnalyzerBridge");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/gui/BeamAnalyzerApp.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);
    return app.exec();
}
