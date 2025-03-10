import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: iosSliderComponent
    property alias value: iosSlider.value

    width: 360
    height: 40

    Slider {
        id: iosSlider
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        from: 0
        to: 100
        value: 50

        style: SliderStyle {
            groove: Rectangle {
                implicitHeight: 6
                radius: 3
                color: "lightgray"
                border.color: "darkgray"

                Rectangle {
                    id: grooveHighlight
                    anchors.left: parent.left
                    width: iosSlider.visualPosition * parent.width
                    height: parent.height
                    radius: 3
                    color: "#007aff" // iOS blue
                }
            }

            handle: Rectangle {
                width: 28
                height: 28
                radius: 14
                color: "white"
                border.color: "#007aff"
                border.width: 1

                Rectangle {
                    anchors.centerIn: parent
                    width: 24
                    height: 24
                    radius: 12
                    color: "white"
                }
            }
        }
    }
}