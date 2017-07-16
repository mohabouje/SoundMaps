import QtQuick 2.4
import QtCharts 2.2
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3
Page {
    width: 400
    height: 400
    padding: 10

    RowLayout {
        anchors.fill: parent
        ChartView {
            anchors.fill: parent
            width: parent.width
            height: parent.height
            title: qsTr("Short Time Analysis")
            titleColor: Material.accent
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
                max: 10
                tickCount: 1

            }

            ValueAxis {
                id: axisY
                min: 0
                max: 1
            }

            LineSeries {
                axisX: axisX
                axisY: axisY
            }
        }
    }
}
