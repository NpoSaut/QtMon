import QtQuick 1.1

Column {
    id: root
    property alias labelText: label.text
    property alias text: parameter.text

    property color accentColor: "#ff0"
    property color regularColor: "#fff"

    Rectangle {
        id: labelContainer
        height: 25
        anchors.left: parent.left
        anchors.right: parent.right
        color: "#00000000"
        Text {
            id: label
            anchors.horizontalCenter: parent.horizontalCenter
            color: accentColor
            font.pixelSize: 18
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
