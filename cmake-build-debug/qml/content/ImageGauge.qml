import QtQuick 2.0


Rectangle {
    color: "lightgray" // Default color

    Component.onCompleted: {
        objectName = baseID;
        console.log("ImageGauge initialized with baseID:", baseID);
    }
}