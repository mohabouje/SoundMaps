import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtLocation 5.9
import QtGraphicalEffects 1.0
import QtCharts 2.2
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
        background: Rectangle {
            color: ThemeManager.accentColor()
        }

        RowLayout {
            anchors.fill: parent
            ImageToolButton {
                iconSource:  "qrc:/icon/navigation_menu.svg"
                iconSize: Qt.size(0.45 * parent.height, 0.45 * parent.height)
                iconColor: "white"
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

            ImageToolButton {
                iconSource: (AudioManager.recorder.active) ? "qrc:/icon/microphone-off.svg" : "qrc:/icon/microphone.svg"
                iconSize: Qt.size(0.45 * parent.height, 0.45 * parent.height)
                iconColor: "white"
                onClicked: AudioManager.recorder.toggle();
            }

            ImageToolButton {
                iconSource:  "qrc:/icon/navigation_more_vert.svg"
                iconSize: Qt.size(0.45 * parent.height, 0.45 * parent.height)
                iconColor: "white"
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

        ShortTimeAnalysisChart {
        }

        Page {

            ListView {
                id: sampleListView
                anchors.fill: parent
                model: ComponentsManager.beaconListModel
                delegate: BeaconListDelegate {
                    beaconSnr: snr
                    beaconName: name
                    beaconState: state
                    beaconPosition: position
                }

                spacing: 4
              }

        }

        Page {

        }

        Page {

        }
    }

    footer: MainTabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        position: TabBar.Footer
        hightlightColor: ThemeManager.accentColor()
        normalColor: ThemeManager.foregroundColor()
    }

    Component.onCompleted: {
        AppDelegate.init()
        AudioManager.reset()
    }
}
