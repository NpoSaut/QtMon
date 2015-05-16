import QtQuick 1.1

Column {
    id: root
    property alias labelColor: label.color
    property color barColor: "#666"
    property color textColor: "#ccc"
    property color borderColor: "#666"

    property int contentPixelSize: labelPixelSize * (20 / 12)
    property int labelPixelSize: 12
    property string labelFontFamily: undefined
    property string contentFontFamily: undefined

    property alias labelText: label.text
    property double value: 0
    property int valueTextFixed: 0
    property double minValue: 0
    property double maxValue: 100
    property string units: ""

    spacing: 2

    Text {
        id: label
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: root.labelPixelSize
        font.family: root.labelFontFamily
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

        BorderPart {
            isBottom: true
            borderColor: root.borderColor
            height: 0.4 * parent.height
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            spacing: 4
            Text {
                color: root.textColor
                text: root.value.toFixed(root.valueTextFixed)
                font.pixelSize: root.contentPixelSize
                font.family: contentFontFamily
            }
            Text {
                anchors.bottom: parent.bottom
                text: units
                color: root.textColor
                font.pixelSize: root.contentPixelSize * 0.7
                font.family: contentFontFamily
            }
        }

        Rectangle {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.margins: 2
            width: (parent.width - 2 * anchors.margins) * (root.value - root.minValue) / (root.maxValue - root.minValue)
            clip: true
            color: "#00000000"
            Rectangle {
                radius: 7
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                width: box.width - 4
                opacity: 0.9
                color: root.barColor
                Row {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 4
                    Text {
                        color: "#000"
                        text: root.value.toFixed(root.valueTextFixed)
                        font.pixelSize: root.contentPixelSize
                        font.family: contentFontFamily
                    }
                    Text {
                        anchors.bottom: parent.bottom
                        color: "#000"
                        text: units
                        font.pixelSize: root.contentPixelSize * 0.7
                        font.family: contentFontFamily
                    }
                }
            }
        }
    }
}
