import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtLocation 5.9
import QtGraphicalEffects 1.0
import QtCharts 2.2
import QtPositioning 5.2
import QtLocation 5.3
import com.mohabouje.soundmaps 1.0
ApplicationWindow {
    id: window
    visible: true
    width: 400
    height: 600
    title: qsTr("Sound Maps")

    header: ToolBar {
        id: toolBar;
        position: ToolBar.Header

        RowLayout {
            anchors.fill: parent
            TabButton {
                checkable: false
                icon.source:  "qrc:/icon/navigation_menu.svg"
                icon.width: 0.45 * parent.height
                icon.height: 0.45 * parent.height
                onClicked: {
                    if (drawer.visible) {
                        drawer.close()
                    } else {
                        drawer.open()
                    }
                }
            }

            Label {
                id: toolbarTitle
                font.pixelSize: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true

            }

            TabButton {
                checkable: false
                icon.source: (AudioManager.recorder.active) ? "qrc:/icon/microphone-off.svg" : "qrc:/icon/microphone.svg"
                icon.width: 0.45 * parent.height
                icon.height: 0.45 * parent.height
                onClicked: AudioManager.recorder.toggle();
            }

            TabButton {
                checkable: false
                icon.source:  "qrc:/icon/navigation_more_vert.svg"
                icon.width: 0.45 * parent.height
                icon.height: 0.45 * parent.height
                onClicked: optionsMenu.open()

                Menu {
                    id: optionsMenu
                    x: parent.width - width
                    transformOrigin: Menu.TopRight
                    MenuItem {
                        text: "Settings"
                        onClicked: {
                            AudioManager.recorder.stop();
                            audioSettingsDialog.show()
                        }
                    }
                    MenuItem {
                        text: "About"
                    }
                }
            }
        }
    }


    AudioSettings {
        id: audioSettingsDialog
        anchors.centerIn: parent
        width: parent.width * 0.75
        height: parent.height * 0.9
        onDialogClosed: AudioManager.reset()
    }

    Drawer {
        id: drawer
        width: 0.75 * Math.min(window.width, window.height)
        height: window.height - header.height
        y: header.height

    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
        padding: 0

        ChartWidget {

        }

        Page {


        }

        Page {

            Plugin {
               id: mapPlugin
               name: "osm" // "mapboxgl", "esri", ...
           }


            PositionSource {
                id: positionSource
                updateInterval: 1000
                active: true
            }

            Map {
                id: map
                anchors.fill: parent
                plugin: mapPlugin
                center: positionSource.position.coordinate
                zoomLevel: 14
            }

        }

        Page {

        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        position: TabBar.Footer
        Repeater {
            model: AbstractModelManager.tabBarModel
            TabButton {
                icon.source: model.icon
            }
        }
    }


    Component.onCompleted: {
        AudioManager.reset()
        positionSource.start()
    }
}
