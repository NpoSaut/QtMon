import QtQuick 1.1

Rectangle {
    id: root
    property alias labelWidth: labelContainer.width
    property alias labelText: label.text
    property alias text: parameter.text
    property alias boxHeight: parameter.boxHeight
    property alias fontHeight: parameter.fontHeight

    property color accentColor: "#ff0"
    property color regularColor: "#fff"
    property alias backgroundColor: parameter.backgroundColor

    height: parameter.boxHeight
    color: "#00000000"

    Rectangle {
        id: labelContainer
        height: parent.height
        anchors.left: parent.left
        color: "#00000000"
        Text {
            id: label
            anchors.right: parent.right
            anchors.rightMargin: 3
            anchors.verticalCenter: parent.verticalCenter
            color: regularColor
            font.pixelSize: fontHeight
        }
    }
    ParameterBox {
        id: parameter
        anchors.left: labelContainer.right
        anchors.right: parent.right
        borderColor: accentColor
        textColor: regularColor
    }
}
