import QtQuick 1.1

Rectangle {
    property alias iconText: icon.text
    property alias backgroundColor: box.backgroundColor
    property alias borderColor: box.borderColor
    property alias iconColor: icon.color
    property alias boxHeight: box.boxHeight
    property int fontHeight: boxHeight - 4

    color: "#00000000"
    height: box.boxHeight

    Box {
        id: box
        anchors.fill: parent
    }

    Text {
        id: icon
        text: "X"
        font.pixelSize: fontHeight
        font.family: "QtMon"
        color: box.borderColor
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
}
