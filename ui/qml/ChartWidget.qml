import QtQuick 2.4
import QtCharts 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import com.mohabouje.soundmaps 1.0
Page {
    width: 400
    height: 400
    padding: 10


    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true
            RadioButton {
                id : lowProcessing
                checked: ChartManager.type == ChartManager.WaveForm
                onClicked: ChartManager.type = (ChartManager.WaveForm)
                text: qsTr("Wave")
            }
            RadioButton {
                checked: ChartManager.type == ChartManager.Energy
                onClicked: ChartManager.type = (ChartManager.Energy)
                text: qsTr("Energy")
            }

            RadioButton {
                checked: ChartManager.type == ChartManager.Pitch
                onClicked: ChartManager.type = (ChartManager.Pitch)
                text: qsTr("Pitch")
            }

            RadioButton {
                checked: ChartManager.type == ChartManager.Spectrogram
                onClicked: ChartManager.type = (ChartManager.Spectrogram)
                text: qsTr("Spectrogram")
            }
        }

        ChartView {
            id: chartView
            Layout.fillWidth: true
            Layout.fillHeight: true
            titleColor: ThemeManager.accentColor()
            antialiasing: false
            backgroundColor: "transparent"
            legend.visible : false
            margins.top : 0
            margins.left : 0
            margins.right : 0
            margins.bottom : 0

            ValueAxis {
                id: axisX
                min: ChartManager.currentBuffer.axisMinX
                max: ChartManager.currentBuffer.axisMaxX
                tickCount: 1

            }

            ValueAxis {
                id: axisY
                min: ChartManager.currentBuffer.axisMinY
                max: ChartManager.currentBuffer.axisMaxY
            }

            LineSeries  {
                id : series
                axisX: axisX
                axisY: axisY
            }
        }
    }

    Timer {
        id: refreshTimer
        interval: ChartManager.refreshRate
        running: true
        repeat: true
        onTriggered: {
            ChartManager.update()
        }
    }

    Component.onCompleted: {
        ChartManager.setSeries(series)
        refreshTimer.start()
    }
}
