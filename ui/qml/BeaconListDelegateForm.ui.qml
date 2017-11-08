import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
    width: 400
    height: 100

    property string beaconName: "Example";
    property string beaconPosition: "(0, 0, 0)";
    property string beaconSnrImage: "qrc:/icon/wifi_levels/if_ic_signal_wifi_0.svg";
    property bool beaconState: false;

    RowLayout {
        id: rowLayout
        anchors.rightMargin: 5
        anchors.leftMargin: 5
        anchors.bottomMargin: 5
        anchors.topMargin: 5
        anchors.fill: parent

        ColumnLayout {
            id: columnLayout
            Layout.preferredHeight: parent.height
            Layout.fillHeight: true

            SwitchDelegate {
                id: switchDelegate
                checked: beaconState
            }
        }
        ColumnLayout {
            id: labelLayout
            Layout.preferredHeight: parent.height
            Layout.fillHeight: true

            Label {
                id: nameLabel
                text: beaconName
                Layout.preferredHeight: 25
                font.bold: true
                font.pointSize: 18
                Layout.fillWidth: true
            }

            Label {
                id: positionLabel
                text: beaconPosition
            }
        }

        Image {
            id: image
            Layout.preferredHeight: 50
            Layout.preferredWidth: 50
            source: beaconSnrImage
        }
    }


}
