import QtQuick 2.0
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3

TabButton {
    id: tabButton
    property bool highlight: false;
    property color highlightColor: "red"
    property color normalColor: "black"
    property size iconSize: Qt.size(0,0)
    property string icon: "";
    property string name: "";
    property int counter: 0;

    ColumnLayout {
        anchors.centerIn: parent
        Rectangle {
            id: imageContainer
            width: parent.width
            Image {
                id: image
                anchors.centerIn: parent
                source: icon
                sourceSize: iconSize
                smooth: true
                visible: false
            }
            ColorOverlay {
                anchors.fill: image
                source: image
                color: (tabButton.checked) ? highlightColor : normalColor;
            }
        }

        Text {
            anchors.topMargin: 10
            anchors.top: imageContainer.bottom
            text: name
            color: (tabButton.checked) ? highlightColor : normalColor;
        }
    }

    Rectangle {
        id: container
        width: 18
        y: image.y + image.height - (0.5 * width)
        x: image.x + 2 * image.width + (0.5 * width)
        height: width
        radius: width*0.5
        opacity: 0.6
        color: "red"
        Text {
          anchors.centerIn: container
          font.pointSize: container.width / 3
          font.bold: true
          color: "white"
          text: counter
        }
        visible: counter > 0
    }
}
