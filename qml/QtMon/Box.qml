import QtQuick 1.1

Rectangle {
    property color borderColor: "#fff"
    property color backgroundColor: "#00000000"
    property int boxHeight: 15

    color: backgroundColor
    border.width: 1
    border.color: borderColor
    height: boxHeight
    width: 100
}
