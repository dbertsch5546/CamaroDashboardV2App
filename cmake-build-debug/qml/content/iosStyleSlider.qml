import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Shapes 6.0

Rectangle {
    id: slider
    width: 300
    height: 60
    radius: 30
    color: "#e0e0e0"
    border.color: "#c0c0c0"
    border.width: 1

    property alias value: handle.x

    signal valueChanged(int value)

    Rectangle {
        id: track
        anchors.fill: parent
        radius: 30
        color: "#cccccc"
    }

    Rectangle {
        id: activeTrack
        height: parent.height
        width: handle.x + handle.width / 2
        radius: 30
        color: "#4CAF50"
    }

    Rectangle {
        id: handle
        width: parent.height
        height: parent.height
        radius: 30
        color: "#ffffff"
        border.color: "#aaaaaa"
        border.width: 1

        Drag.active: dragArea.drag.active
        Drag.hotSpot.x: width / 2
        Drag.hotSpot.y: height / 2

        MouseArea {
            id: dragArea
            anchors.fill: parent
            drag.target: handle
            onReleased: {
                slider.valueChanged(handle.x + handle.width / 2)
            }
        }

        Behavior on x {
            NumberAnimation {
                duration: 250
            }
        }

        onXChanged: {
            if (handle.x < 0) {
                handle.x = 0
            } else if (handle.x > slider.width - handle.width) {
                handle.x = slider.width - handle.width
            }
        }
    }
}
