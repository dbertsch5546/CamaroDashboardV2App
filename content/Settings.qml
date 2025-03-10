import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts 6.2
import QtQuick.Dialogs 6.2
import QtQuick.VirtualKeyboard 6.2

Rectangle {
    id: secondPage
    width: 800
    height: 480
    //color: "black"
    Image {
        id: backgroundImage
        source: "file:///home/dbertsch/images/backgrounds_195_610.jpg"
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop // Adjust this if needed
    }

    property string canInterfaceName: "vcan0"
    property string logUpdateFrequency: "1000"

    CustomSlider{
        id: slider
        x: 10
        y: 150
        width: 50
        height: 15
    }

    Label {
        x: 10
        y: 10
        text: "CAN Interface:"
        color: "white"
        font.pixelSize: 20
        Layout.alignment: Qt.AlignVCenter
    }

    TextField {
        id: canInterfaceInputField
        objectName: "canInterfaceInputField"
        placeholderText: ""
        x: 300
        y: 10
        width: 300
        color: "white"
        placeholderTextColor: "white"
        font.pixelSize: 20
        background: Rectangle {
            color: "transparent"
            border.color: "white"
            border.width: 2
            radius: 5
        }
        text: settingsHandler.canInterfaceName
        onTextChanged: {
            canInterfaceName = text
        }
        onActiveFocusChanged: {
            inputPanel.visible = activeFocus
        }
    }

    Label {
        x: 10
        y: 80
        text: "Log Update Frequency (ms):"
        color: "white"
        font.pixelSize: 20
        Layout.alignment: Qt.AlignVCenter
    }

    TextField {
        id: frequencyField
        objectName: "frequencyField"
        placeholderText: ""
        x: 300
        y: 80
        width: 300
        color: "white"
        placeholderTextColor: "white"
        font.pixelSize: 20
        background: Rectangle {
            color: "transparent"
            border.color: "white"
            border.width: 2
            radius: 5
        }
        text: settingsHandler.logUpdateFrequency
        onTextChanged: {
            logUpdateFrequency = text
        }
        onActiveFocusChanged: {
            inputPanel.visible = activeFocus
        }
    }

    Button {
        text: "Start CAN Simulator"
        x: 10
        y: 200
        width: 250
        height: 50
        background: Rectangle {
            color: "lightgreen"
            border.color: "black"
            radius: 10
        }
        onClicked: {
            // Call the function to start CAN simulator
            settingsHandler.handleStartCanSimulatorClicked()
        }
    }

    Button {
        text: "Stop CAN Simulator"
        x: 10
        y: 275
        width: 250
        height: 50
        background: Rectangle {
            color: "lightcoral"
            border.color: "black"
            radius: 10
        }
        onClicked: {
            // Call the function to stop CAN simulator
            settingsHandler.handleStopCanSimulatorClicked()
        }
    }


    /*
    ColumnLayout {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 10
        spacing: 20

        RowLayout {
            spacing: 10

            Label {
                text: "CAN Interface:"
                color: "white"
                font.pixelSize: 20
                Layout.alignment: Qt.AlignVCenter
            }

            TextField {
                id: canInterfaceInputField
                objectName: "canInterfaceInputField"
                placeholderText: ""
                width: 300
                color: "white"
                placeholderTextColor: "white"
                font.pixelSize: 20
                background: Rectangle {
                    color: "transparent"
                    border.color: "white"
                    border.width: 2
                    radius: 5
                }
                text: settingsHandler.canInterfaceName
                onTextChanged: {
                    canInterfaceName = text
                }
                onActiveFocusChanged: {
                    inputPanel.visible = activeFocus
                }
            }
        }

        RowLayout {
            spacing: 10

            Label {
                text: "Log Update Frequency (ms):"
                color: "white"
                font.pixelSize: 20
                Layout.alignment: Qt.AlignVCenter
            }

            TextField {
                id: frequencyField
                objectName: "frequencyField"
                placeholderText: ""
                width: 300
                color: "white"
                placeholderTextColor: "white"
                font.pixelSize: 20
                background: Rectangle {
                    color: "transparent"
                    border.color: "white"
                    border.width: 2
                    radius: 5
                }
                text: settingsHandler.logUpdateFrequency
                onTextChanged: {
                    logUpdateFrequency = text
                }
                onActiveFocusChanged: {
                    inputPanel.visible = activeFocus
                }
            }
        }

        RowLayout {
            spacing: 10

            ColumnLayout {
                spacing: 0  // No spacing between buttons

                Button {
                    text: "Start CAN Simulator"
                    width: 200
                    height: 50
                    Layout.alignment: Qt.AlignLeft
                    background: Rectangle {
                        color: "lightgreen"
                        border.color: "black"
                        radius: 10
                    }
                    font.pixelSize: 20
                    padding: 0  // No padding
                    onClicked: {
                        // Call the function to start CAN simulator
                        settingsHandler.handleStartCanSimulatorClicked()
                    }
                    scale: 0.5
                }

                Button {
                    text: "Stop CAN Simulator"
                    width: 200
                    height: 50
                    Layout.alignment: Qt.AlignLeft
                    background: Rectangle {
                        color: "lightcoral"
                        border.color: "black"
                        radius: 10
                    }
                    font.pixelSize: 20
                    padding: 0  // No padding
                    onClicked: {
                        // Call the function to stop CAN simulator
                        settingsHandler.handleStopCanSimulatorClicked()
                    }
                    scale: 0.5
                }
            }
        }
    }
    */
    Button {
        text: "Go Back"
        width: 150
        height: 50
        background: Rectangle {
            color: "lightgray"
            border.color: "black"
            radius: 10
        }
        font.pixelSize: 20
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 10
        onClicked: {
            loader.source = ""
            inputPanel.visible = false
        }
        scale: 0.5
    }

    Button {
        text: "Save"
        width: 150
        height: 50
        background: Rectangle {
            color: "lightgray"
            border.color: "black"
            radius: 10
        }
        font.pixelSize: 20
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 10
        onClicked: {
            settingsHandler.handleSaveClicked(canInterfaceName, logUpdateFrequency)
            saveDialog.open()
            inputPanel.visible = false
        }
        scale: 0.5
    }

    Dialog {
        id: saveDialog
        title: "Settings Saved"
        modal: true
        standardButtons: Dialog.Ok

        Label {
            text: "Your settings have been saved successfully."
            font.pixelSize: 16
            padding: 20
        }
    }

    // Add the virtual keyboard
    InputPanel {
        id: inputPanel
        z: 99
        anchors.fill: parent
        visible: false

        // Custom button to hide the keyboard
        Rectangle {
            id: hideButton
            width: 100
            height: 40
            color: "red"
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.margins: 10
            radius: 10

            Text {
                anchors.centerIn: parent
                text: "Hide Keyboard"
                color: "white"
                font.pixelSize: 14
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    Qt.inputMethod.hide()
                    // Ensure the InputPanel is also hidden
                    inputPanel.visible = false
                }
            }
        }
    }
}
