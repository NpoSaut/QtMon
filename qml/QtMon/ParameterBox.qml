import QtQuick 1.1

Rectangle {
    property alias text: label.text
    property alias textColor: label.color
    property color borderColor: "#fff"
    property color backgroundColor: "#00000000"
    property int boxHeight: 25
    property int fontHeight: boxHeight - 8

    color: backgroundColor
    border.width: 1
    border.color: borderColor
    height: boxHeight
    width: 100
    Text {
        id: label
        font.pixelSize: fontHeight
        font.family: "Calibri"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
}
