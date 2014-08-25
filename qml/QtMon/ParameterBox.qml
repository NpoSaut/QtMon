import QtQuick 1.1

Rectangle {
    property alias text: label.text
    property alias textColor: label.color
    property color borderColor: "#fff"

    color: "#00000000"
    border.width: 1
    border.color: borderColor
    height: 25
    width: 100
    Text {
        id: label
        font.pixelSize: 18
        font.family: "Calibri"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
}
