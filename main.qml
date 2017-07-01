import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Sound Maps")

    FontLoader { id: androidFont; name: "Material Icons"; source: Qt.resolvedUrl("android-fonts/iconfont/MaterialIcons-Regular.ttf"); }
    FontLoader { id: uwpFont; name: "FontUIP"; source: Qt.resolvedUrl("uwp-fonts/Symbols/winjs-symbols.ttf"); }
    FontLoader { id: fontAwesome; name: "FontAwesome"; source: Qt.resolvedUrl(":/Font-Awesome/fonts/fontawesome-webfont.ttf"); }

    header: ToolBar {
        id: toolBar;
        position: ToolBar.Header
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: qsTr("‹")
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
            font.pixelSize: 24
            font.pointSize: 100
            font.family: fontAwesome
            text: "\uf20e"
        }
        TabButton {
            text: qsTr("Second")
        }
    }
}
