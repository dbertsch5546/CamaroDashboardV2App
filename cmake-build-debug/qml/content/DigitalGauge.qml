import QtQuick 2.0

Rectangle {
    color: "lightgray" // Default color

    Component.onCompleted: {
        objectName = baseID;
        console.log("DigitalGauge initialized with baseID:", baseID);
    }
}