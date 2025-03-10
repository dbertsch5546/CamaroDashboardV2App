import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: iosToggleSlider
    width: 60
    height: 30
    radius: height / 2
    color: slider.value === 1 ? "#4cd964" : "#e5e5ea"
    border.color: "#d1d1d6"
    border.width: 1

    property alias value: slider.value

    Slider {
        id: slider
        anchors.fill: parent
        from: 0
        to: 1
        stepSize: 1
        value: 0
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
        x: slider.value === 1 ? parent.width - width - 1 : 1
        Behavior on x {
            NumberAnimation {
                duration: 200
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            slider.value = slider.value === 0 ? 1 : 0
        }
    }
}
