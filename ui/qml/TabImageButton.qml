import QtQuick 2.0
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0
import com.mohabouje.soundmaps 1.0

TabButton {
    id: tabButton
    property color highlightColor:  ThemeManager.accentColor()
    property color normalColor: ThemeManager.foregroundColor()
    property string icon: "";
    Rectangle {
        anchors.fill: parent
        Image {
            id: image
            anchors.centerIn: parent
            source: icon
            sourceSize: Qt.size(0.60 * parent.height,  0.60 * parent.height)
            smooth: true
            visible: false
        }
        ColorOverlay {
            anchors.fill: image
            source: image
            color: (tabButton.checked) ? highlightColor : normalColor;
        }
    }
}
