import QtQuick 1.1

Rectangle {
    id: root
    property alias text: box.text
    property color accentColor: "#fff"
    property color textColor: "#fff"
    property bool isActive: false
    property alias boxHeight: box.boxHeight
    property alias fontHeight: box.fontHeight

    height: boxHeight

    color: "#00000000"

    ParameterBox {
        id: box
        height: parent.height
        width: parent.width
        backgroundColor: isActive == true ? root.accentColor : "#00000000"
        borderColor: accentColor
        textColor: root.isActive == true ? "#000" : parent.textColor
    }
}
