import QtQuick 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.0
import com.mohabouje.soundmaps 1.0
Item {
    anchors.centerIn: parent
    width: 450
    height: 350
    Dialog {
        id: dialog
        width: parent.width
        height: parent.height
        standardButtons: Dialog.Ok
        modal: true
        onAccepted: {
            close()
        }
        onClosed: {
            AppDelegate.audioRecorder.initialize();
        }
        onOpened: {
            AppDelegate.audioRecorder.stop()
        }

        padding: 10

        header: Rectangle {
            visible: false
            color: Material.primary
            width: parent.width
            height: 40
        }

        Rectangle {
            id: groupBox
            width: parent.width
            ColumnLayout {
                width: parent.width

                Label {
                    text: qsTr("Device")
                }
                ComboBox {
                    editable: false
                    model: AppDelegate.audioRecorder.availableDevices()
                    onCurrentTextChanged: (AppDelegate.audioRecorder.device = currentText)
                    Layout.fillWidth: true
                }

                Label {
                    text: qsTr("Frequency")
                }
                ComboBox {
                    id: comboBox
                    model: AppDelegate.audioRecorder.supportedSampleRates
                    onCurrentTextChanged: AppDelegate.audioRecorder.sampleRate = parseInt(currentText)
                    Layout.fillWidth: true
                }
                Label {
                    text: qsTr("Frame Rate")
                }
                ColumnLayout {
                    id: slider
                    Layout.fillWidth: true
                    RadioButton {
                        id : lowProcessing
                        checked: AppDelegate.audioRecorder.bufferDuration == AudioRecorder.Low
                        onClicked: AppDelegate.audioRecorder.setBufferDuration(AudioRecorder.Low)
                        text: qsTr("Low (10 FPS)")
                    }
                    RadioButton {
                        id : mediumProcessing
                        checked: AppDelegate.audioRecorder.bufferDuration == AudioRecorder.Medium
                        onClicked: AppDelegate.audioRecorder.setBufferDuration(AudioRecorder.Medium)
                        text: qsTr("Medium (20 FPS)")
                    }

                    RadioButton {
                        id : highProcessing
                        checked: AppDelegate.audioRecorder.bufferDuration == AudioRecorder.High
                        onClicked: AppDelegate.audioRecorder.setBufferDuration(AudioRecorder.High)
                        text: qsTr("Hight (40 FPS)")
                    }
                }
            }
        }
    }

    function show() {
        dialog.open();
    }
}
