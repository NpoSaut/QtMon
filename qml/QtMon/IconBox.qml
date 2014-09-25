import QtQuick 1.1

Rectangle {
    property alias iconSource: icon.source
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

    Image {
        id: icon
        source: "file"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
}
