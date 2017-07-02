import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.1
import QtQuick.Window 2.2
import com.mohabouje.soundmaps 1.0

TabBar {
    id: tabBar
    position: TabBar.Footer
    property real screenDensity: Screen.pixelDensity
    property real tabBarIconSize: 3 * screenDensity;
    property color hightlightColor: Qt.red
    property color normalColor: Qt.black

    Repeater {
        model: tabBarModel
        MainTabButton {
            name: model.name
            counter: model.counter
            icon: model.icon
            highlightColor: tabBar.hightlightColor
            normalColor: tabBar.normalColor
            iconSize: Qt.size(tabBarIconSize, tabBarIconSize)
        }
    }

    TabBarModel {
        id: tabBarModel
    }
}
