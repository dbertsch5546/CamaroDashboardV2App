import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: iosSwitch
    property alias checked: switchControl.checked

    width: 60
    height: 30
    radius: height / 2
    color: switchControl.checked ? "#4cd964" : "#e5e5ea"
    border.color: "#d1d1d6"
    border.width: 1

    Switch {
        id: switchControl
        visible: false
    }

    Rectangle {
        id: handle
        width: 28
        height: 28
        radius: height / 2
        color: "white"
        border.color: "#d1d1d6"
        border.width: 1
        anchors.verticalCenter: parent.verticalCenter
        x: switchControl.checked ? parent.width - width - 1 : 1
        Behavior on x {
            NumberAnimation {
                duration: 200
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            switchControl.checked = !switchControl.checked
        }
    }
}
