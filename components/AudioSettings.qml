import QtQuick 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import com.mohabouje.soundmaps 1.0
Item {
    anchors.centerIn: parent
    width: 450
    height: 350
    Dialog {
        id: dialog
        width: parent.width
        height: parent.height
        title: qsTr("Audio Settings")
        standardButtons: Dialog.Ok
        modal: true
        onAccepted: close()
        padding: 10
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
                    text: qsTr("Buffer Size")
                }
                ColumnLayout {
                    id: slider
                    Layout.fillWidth: true
                    RadioButton {
                        id : lowProcessing
                        checked: AppDelegate.audioRecorder.bufferDuration == AudioRecorder.Low
                        onClicked: AppDelegate.audioRecorder.setBufferDuration(AudioRecorder.Low)
                        text: qsTr("Low")
                    }
                    RadioButton {
                        id : mediumProcessing
                        checked: AppDelegate.audioRecorder.bufferDuration == AudioRecorder.Medium
                        onClicked: AppDelegate.audioRecorder.setBufferDuration(AudioRecorder.Medium)
                        text: qsTr("Medium")
                    }

                    RadioButton {
                        id : highProcessing
                        checked: AppDelegate.audioRecorder.bufferDuration == AudioRecorder.High
                        onClicked: AppDelegate.audioRecorder.setBufferDuration(AudioRecorder.High)
                        text: qsTr("Hight")
                    }
                }
            }
        }
    }

    function show() {
        dialog.open();
    }
}
