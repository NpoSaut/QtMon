import QtQuick 1.1

Column {
    id: root
    property alias labelText: label.text
    property alias text: parameter.text
    property alias boxHeight: parameter.boxHeight
    property alias fontHeight: parameter.fontHeight

    property color accentColor: "#ff0"
    property color regularColor: "#fff"

    Rectangle {
        id: labelContainer
        anchors.left: parent.left
        anchors.right: parent.right
        height: label.height
        color: "#00000000"
        Text {
            id: label
            anchors.horizontalCenter: parent.horizontalCenter
            color: accentColor
            font.pixelSize: fontHeight
            font.family: "Calibri"
        }
    }
    ParameterBox {
        id: parameter
        anchors.left: parent.left
        anchors.right: parent.right
        borderColor: accentColor
        textColor: regularColor
    }
}
