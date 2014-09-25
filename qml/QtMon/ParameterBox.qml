import QtQuick 1.1

Rectangle {
    property alias text: label.text
    property alias textColor: label.color
    property alias backgroundColor: box.backgroundColor
    property alias borderColor: box.borderColor
    property alias boxHeight: box.height
    property int fontHeight: boxHeight - 8

    color: "#00000000"
    height: box.height

    Box {
        id: box
        anchors.fill: parent
    }

    Text {
        id: label
        font.pixelSize: fontHeight
        font.family: "Calibri"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
}
