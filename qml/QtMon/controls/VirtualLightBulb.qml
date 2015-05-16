import QtQuick 1.1

Rectangle {
    id: root
    property int fontPixelSize: 20
    property color bulbColor: "#f00"
    property color textColor: "#000"
    property bool isActive: true
    property string text: "X"

    width: Math.sqrt(2) * fontPixelSize + 2
    height: width
    radius: width/2

    color: isActive ? bulbColor : "#00000000"

    Text {
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: "icons"
        font.pixelSize: fontPixelSize
        color: textColor
        visible: isActive
        text: root.text
    }
}
