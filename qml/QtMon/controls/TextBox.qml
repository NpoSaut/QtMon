import QtQuick 1.1

Column {
    id: root
    property alias labelColor: label.color
    property color contentColor: "#666"
    property color borderColor: "#666"

    property int contentPixelSize: labelPixelSize * (20 / 12)
    property int labelPixelSize: 12
    property string labelFontFamily: undefined
    property string contentFontFamily: undefined

    property alias labelText: label.text
    property alias text: content.text
    property alias units: unitsLabel.text

    spacing: 2

    Text {
        id: label
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: root.labelPixelSize
        font.family: labelFontFamily
        font.bold: true
    }
    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        height: contentPixelSize * 1.4

        id: box
        color: "#00000000"

        BorderPart {
            borderColor: root.borderColor
            height: 0.4 * parent.height
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            spacing: 4
            Text {
                id: content
                color: root.contentColor
                font.pixelSize: root.contentPixelSize
                font.family: contentFontFamily
            }
            Text {
                id: unitsLabel
                anchors.bottom: parent.bottom
                color: root.contentColor
                font.pixelSize: root.contentPixelSize * 0.7
                font.family: contentFontFamily
            }
        }
    }
}
