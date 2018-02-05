import QtQuick 2.4

Item {
    width: 400
    height: 400

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 400
        height: 90
        color: "#021578"
    }

    Connections {
        target: rectangle
        onClicked: print("clicked")
    }
}
