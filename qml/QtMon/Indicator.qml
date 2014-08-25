import QtQuick 1.1

Rectangle {
    id: root
    property alias text: label.text
    property color accentColor: "#fff"
    property color textColor: "#fff"
    property bool isActive: false

    height: 25

    border.width: 1
    border.color: accentColor
    color: isActive == true ? root.accentColor : "#00000000"

    Text {
        id: label
        font.pixelSize: 18
        font.family: "Calibri"
        color: root.isActive == true ?
                 "#000" :
                 textColor
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
}
