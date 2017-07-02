import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.1
import QtQuick.Window 2.2

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Sound Maps")

    property real screenDensity: Screen.pixelDensity
    property real toolBarIconSize: 4 * screenDensity;
    property real tabBarIconSize: 7.5 * screenDensity;

    header: ToolBar {
        id: toolBar;
        position: ToolBar.Header
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: ""
                Image {
                    id: homeIcon
                    anchors.centerIn: parent
                    source: "qrc:/icon/menu.svg"
                    sourceSize: Qt.size(toolBarIconSize, toolBarIconSize)
                    smooth: true
                    visible: false
                }

                ColorOverlay {
                    anchors.fill: homeIcon
                    source: homeIcon
                    color: Material.background;
                }

                onClicked: {
                    if (drawer.visible) {
                        drawer.close()
                    } else {
                        drawer.open()
                    }
                    drawerList.currentIndex = -1
                }
            }
            Label {
                id: toolbarTitle
                text: tabBar.itemAt(tabBar.currentIndex).text
                font.pixelSize: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true

            }
            ToolButton {
                text: ":"
                onClicked: optionsMenu.open()

                Menu {
                    id: optionsMenu
                    x: parent.width - width
                    transformOrigin: Menu.TopRight
                    MenuItem {
                        text: "Settings"
                    }
                    MenuItem {
                        text: "About"
                    }
                }
            }
        }
    }

    Drawer {
        id: drawer
        width: 0.75 * Math.min(window.width, window.height)
        height: window.height - header.height
        y: header.height

        ListView {
            id: drawerList
            focus: true
            currentIndex: -1
            anchors.fill: parent

            delegate: ItemDelegate {
                width: parent.width
                text: model.title
                highlighted: ListView.isCurrentItem
                onClicked: {
                    listView.currentIndex = index
                    drawer.close()
                }
            }
            model: ListModel {
            }
            ScrollIndicator.vertical: ScrollIndicator { }
        }
    }


    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        AudioWaveChartFragment {
        }

        Page {
            Label {
                text: qsTr("Second page")
                anchors.centerIn: parent
            }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        position: TabBar.Footer
        TabButton {
            id: papa
            Image {
                id: bug
                anchors.centerIn: parent
                source: "qrc:/icon/access-point.svg"
                sourceSize: Qt.size(tabBarIconSize, tabBarIconSize)
                smooth: true
                visible: false
            }

            ColorOverlay {
                anchors.fill: bug
                source: bug
                color: (tabBar.currentItem == papa) ? Material.accent : Material.foreground;
            }

        }
        TabButton {
            text: qsTr("Second")
        }
    }
}
