import QtQuick 1.1

Rectangle {
    id: root
    property bool isBottom: false
    property color borderColor: "#666"
    property int cornerRadius: 8

    color: "#00000000"
    anchors.top: root.isBottom ? undefined : parent.top
    anchors.bottom: root.isBottom ? parent.bottom : undefined
    anchors.left: parent.left
    anchors.right: parent.right
    clip: true

    Rectangle {
        anchors.top: root.isBottom ? undefined : parent.top
        anchors.bottom: root.isBottom ? parent.bottom : undefined
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.rightMargin: 1
        anchors.bottomMargin: 1
        height: parent.height * 2
        color: "#00000000"
        border.color: root.borderColor
        radius: root.cornerRadius
    }
}
