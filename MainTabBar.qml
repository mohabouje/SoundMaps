import QtQuick 2.0
import QtQuick.Controls 2.0
import com.mohabouje.soundmaps 1.0

TabBar {
    id: tabBar
    position: TabBar.Footer
    property color hightlightColor: Qt.red
    property color normalColor: Qt.black

    Repeater {
        model: tabBarModel
        TabImageButton {
            icon: model.icon
            highlightColor: tabBar.hightlightColor
            normalColor: tabBar.normalColor
        }
    }

    TabBarModel {
        id: tabBarModel
    }
}
