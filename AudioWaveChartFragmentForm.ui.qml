import QtQuick 2.7
import QtCharts 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {


    RowLayout {
        id: rowLayout
        x: parent.x
        y: parent.y
        width: parent.width
        height: displayLPC.height

        Label {
            text: qsTr("Display LPC Parameters")
            font.pixelSize: 12
            font.italic: true
            elide: Label.ElideRight
            horizontalAlignment: Qt.AlignHCenter | Qt.AlignRight
            verticalAlignment: Qt.AlignVCenter
            Layout.fillWidth: true
        }


        Switch {
            id: displayLPC
            x: 97
            y: 180
            text: ""
            checked: true
        }
    }



}
