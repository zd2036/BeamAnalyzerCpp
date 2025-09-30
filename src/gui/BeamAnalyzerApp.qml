import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Beam.Camera 1.0
import Beam.Analyzer 1.0

ApplicationWindow {
    id: win
    visible: true
    width: 1000; height: 640
    title: "BeamAnalyzerCpp - Prototype (Qt Quick)"

    CameraProvider { id: cam }
    AnalyzerBridge { id: analyzer }

    Row {
        anchors.fill: parent
        spacing: 8
        Rectangle {
            width: parent.width*0.65; height: parent.height; color: "#222"
            Column {
                anchors.fill: parent
                spacing: 8
                Image { id: preview; anchors.horizontalCenter: parent.horizontalCenter; width: parent.width*0.95; height: parent.height*0.85; fillMode: Image.PreserveAspectFit; source: "" }
                Row {
                    spacing: 10
                    Button { text: cam.live ? "Stop" : "Live Mode"; onClicked: { if (cam.live) cam.stop(); else cam.start(); } }
                    Button { text: "Analyze Frame"; onClicked: { if (preview.paintedSource) analyzer.analyzeImage(preview.paintedSource); } }
                }
            }
        }
        Rectangle {
            width: parent.width*0.35; height: parent.height; color: "#333"
            Column { anchors.fill: parent; spacing: 10; padding: 10
                Text { text: "Results"; font.pixelSize: 20; color: "white" }
                GridLayout { columns:2; columnSpacing: 6; rowSpacing: 6
                    Text { text: "Centroid X:"; color: "white" }
                    Text { text: analyzer.beamData.cx.toFixed(2) }
                    Text { text: "Centroid Y:"; color: "white" }
                    Text { text: analyzer.beamData.cy.toFixed(2) }
                    Text { text: "D4σ X:"; color: "white" }
                    Text { text: analyzer.beamData.D4x.toFixed(2) }
                    Text { text: "D4σ Y:"; color: "white" }
                    Text { text: analyzer.beamData.D4y.toFixed(2) }
                }
            }
        }
    }

    Connections {
        target: cam
        onFrameReady: {
            preview.source = ""; // clear previous
            preview.paintedSource = frame;
        }
    }

    Connections {
        target: analyzer
        onAnalysisDone: {
            // placeholder for any UI update after analysis
        }
    }
}
