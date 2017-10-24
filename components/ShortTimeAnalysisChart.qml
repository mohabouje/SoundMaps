import QtQuick 2.4
import QtCharts 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import com.mohabouje.soundmaps 1.0
Page {
    width: 400
    height: 400
    padding: 10

    RowLayout {
        anchors.fill: parent
        ChartView {
            id: chartView
            anchors.fill: parent
            width: parent.width
            height: parent.height
            title: qsTr("Short Time Analysis")
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
                min: 0
                max: 100
                tickCount: 1

            }

            ValueAxis {
                id: axisY
                min: -1
                max: 1
            }

            LineSeries {
                id : series
                axisX: axisX
                axisY: axisY
            }
        }

        Timer {
            id: refreshTimer
            interval: AppDelegate.audioManager.refreshRate
            running: true
            repeat: true
            onTriggered: {
                AppDelegate.audioManager.audioSeries.update(series);
            }
        }

    }
    Component.onCompleted: {
        refreshTimer.start()
    }
}
