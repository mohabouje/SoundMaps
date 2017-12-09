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
                min: ComponentsManager.spectrogramSeries.axisMinX
                max: ComponentsManager.spectrogramSeries.axisMaxX
                tickCount: 1

            }

            ValueAxis {
                id: axisY
                min: ComponentsManager.spectrogramSeries.axisMinY
                max: ComponentsManager.spectrogramSeries.axisMaxY
            }

            LineSeries {
                id : series
                axisX: axisX
                axisY: axisY
            }
        }

        Timer {
            id: refreshTimer
            interval: ComponentsManager.refreshRate
            running: true
            repeat: true
            onTriggered: {
                ComponentsManager.spectrogramSeries.update()
            }
        }

    }
    Component.onCompleted: {
        ComponentsManager.spectrogramSeries.setSeries(series)
        refreshTimer.start()
    }
}
