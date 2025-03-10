/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.2
import QtQuick.Controls 6.2
import com.example1 1.0
import com.example2 1.0
import com.example3 1.0
import com.example4 1.0
import com.example5 1.0
Rectangle {
    id: rectangle
    width: 800
    height: 480

    Image {
        id: backgroundImage
        source: "file:///home/dbertsch/images/backgrounds_195_610.jpg"
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop // Adjust this if needed
    }

    Rpm_dial_195_83 {
        id: rpmDial
        width: 300
        height: 300
        x: (480 / 2) - 75
        y: 0
        displayRpm: RPMProvider.displayRpm
        rpmFrame: RPMProvider.rpmFrame
        scale: 0.75
    }
    ImageGauge{
        objectName: "speedometer"
        imagePrefix: "file:///home/dbertsch/images/SpeedGauge"
        x: 310
        y: 220
        width: 385
        height: 300
        scale: 0.30
    }
    ImageGauge {
        objectName: "leftTurnSignal"
        imagePrefix: "file:///home/dbertsch/images/arrow_left_solid.png"
        x: 0
        y: 0
        width: 100
        height: 100
    }

    ImageGauge {
        objectName: "rightTurnSignal"
        imagePrefix: "file:///home/dbertsch/images/arrow_right_solid.png"
        x: 700
        y: 0
        width: 100
        height: 100
    }

    ImageGauge {
        objectName: "headlights"
        imagePrefix: "file:///home/dbertsch/images/light_low_beam.png"
        x: 500
        y: 425
        width: 50
        height: 50
    }

    ImageGauge {
        objectName: "highbeams"
        imagePrefix: "file:///home/dbertsch/images/light_high_beam.png"
        x: 550
        y: 425
        width: 50
        height: 50
    }

    ImageGauge {
        objectName: "coolantGauge"
        imagePrefix: "file:///home/dbertsch/images/CoolantGauge"
        x: -25
        y: 220
        width: 250
        height: 250
        scale: .90
    }

    ImageGauge {
        objectName: "oilPressureGauge"
        imagePrefix: "file:///home/dbertsch/images/oilGauge"
        x: -25
        y: 270
        width: 250
        height: 250
        scale: .90
    }

    ImageGauge {
        objectName: "fuelGauge"
        imagePrefix: "file:///home/dbertsch/images/FuelGauge"
        x: -25
        y: 320
        width: 250
        height: 250
        scale: .90
    }

    DigitalGauge {
        objectName: "digitalGauge1"
        x: 5
        y: 25
        width: 100
        height: 100
        scale: .90
    }

    DigitalGauge {
        objectName: "digitalGauge2"
        x: 110
        y: 25
        width: 100
        height: 100
        scale: .90
    }

    DigitalGauge {
        objectName: "digitalGauge3"
        x: 5
        y: 100
        width: 100
        height: 100
        scale: .90
    }

    DigitalGauge {
        objectName: "digitalGauge4"
        x: 110
        y: 100
        width: 100
        height: 100
        scale: .90
    }

    LogWidget {
        objectName: "logWidget"
        x: 550
        y: 90
        width: 400
        height: 400
    }

    DigitalInputIndicator{
        objectName: "digInput1"
        x: 0
        y: 150 + 25
        width: 100
        height: 100
        scale: .90
    }
    DigitalInputIndicator{
        objectName: "digInput2"
        x: 80
        y: 150 + 25
        width: 100
        height: 100
        scale: .90
    }
    DigitalInputIndicator{
        objectName: "digInput3"
        x: 0
        y: 225 + 25
        width: 100
        height: 100
        scale: .90
    }
    DigitalInputIndicator{
        objectName: "digInput4"
        x: 80
        y: 225 + 25
        width: 100
        height: 100
        scale: .90
    }
    Button {
        text: "Settings"
        anchors.bottom: parent.bottom
        x: 650
        width: 150
        height: 50
        background: Rectangle {
            color: "lightgray"
            border.color: "black"
            radius: 10 // Square with slightly rounded corners
        }
        font.pixelSize: 10
        onClicked: {
            loader.source = "Settings.qml"
        }
        scale: 0.75
    }

    Loader {
        id: loader
        anchors.fill: parent
    }
}
