import QtQuick 2.4
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0
import com.mohabouje.soundmaps 1.0


ToolButton {
    property size  iconSize: "25x25"
    property url   iconSource: ""
    property color iconColor: ThemeManager.accentColor()
    text: ""
    Image {
        id: icon
        anchors.centerIn: parent
        source: iconSource
        sourceSize: iconSize
        smooth: true
        visible: false
    }

    ColorOverlay {
        anchors.fill: icon
        source: icon
        color: iconColor
    }
}
