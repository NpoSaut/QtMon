import QtQuick 1.1
import "../controls"

Rectangle {
    id: root
    color: "#000"
    property int labelPixelSize: 12
    property string labelFontFamily: "Courier New"
    property string contentFontFamily: "Courier New"
    property color gridColor: "#00f"
    property color labelsColor: "#0ff"
    property color contentColor: "#ff0"
    property color accentColor: "#f00"
    property color warningRed: "#f00"
    property color warningYellow: "#ff0"

    property color pressureColorA: "#D9D0AB"
    property color pressureColorB: "#7ABE42"

    property string date: "0:0:0"
    property string time: "0:0:0"
    property double speed: 88

    function pad(n, width, z) {
      z = z || '0';
      n = n + '';
      return n.length >= width ? n : new Array(width - n.length + 1).join(z) + n;
    }

    Rectangle {
        anchors.horizontalCenter: root.horizontalCenter
        anchors.verticalCenter: root.verticalCenter
        anchors.verticalCenterOffset: -100
        width: 300
        height: 200
        color: "#00000000"
        Text {
            color: root.labelsColor; font.family: root.labelFontFamily; font.pixelSize: labelPixelSize
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 25
            text: "об/мин x1000"
        }
        AngleMeter {
            anchors.centerIn: parent
            width: parent.width
            height: parent.height
            tickColor: gridColor
            tickLabelColor: labelsColor
            needleColor: "#00000000"
            needleAccents: [ Qt.darker(root.accentColor), root.accentColor ]
            fontFamily: labelFontFamily
            minAngle: 90 + 30
            maxAngle: 90 - 30
            minValue: 0
            maxValue: 4
            step: 4
            cutRadius: 1 / 2
            smallTicksPerStep: 4
            values: [ 0.7, 0.8 ]
        }
        Text {
            color: root.labelsColor; font.family: root.labelFontFamily; font.pixelSize: labelPixelSize; font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.top
            anchors.bottomMargin: 5
            text: "Дизельный двигатель"
        }
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 60
            spacing: 30
            Repeater {
                model: [
                    { label: "Заданная", value: 700, color: Qt.darker(root.accentColor) },
                    { label: "Текущая",  value: 800, color: root.accentColor }
                ]
                Column {
                    spacing: -4
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.family: root.contentFontFamily;
                        color: modelData.color
                        font.pixelSize: labelPixelSize * (20 / 12)
                        text: modelData.value
                    }
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.family: root.labelFontFamily; font.bold: true;
                        color: root.labelsColor
                        font.pixelSize: labelPixelSize
                        text: modelData.label
                    }
                }
            }
        }
    }

    Column {
        anchors.horizontalCenter: root.horizontalCenter
        anchors.verticalCenter: root.verticalCenter
        anchors.horizontalCenterOffset: -root.width * 3 / 8
        anchors.verticalCenterOffset: -root.height * 9 / 24

        spacing: 2

        TextBox {
            labelColor: root.labelsColor
            borderColor: root.gridColor
            contentColor: root.contentColor
            labelPixelSize: root.labelPixelSize

            labelFontFamily: root.labelFontFamily
            contentFontFamily: root.contentFontFamily

            width: 100
            labelText: "Тип масла"
            text: "МГЕ-46"
        }
        TextBox {
            labelColor: root.labelsColor
            borderColor: root.gridColor
            contentColor: root.contentColor
            labelPixelSize: root.labelPixelSize

            labelFontFamily: root.labelFontFamily
            contentFontFamily: root.contentFontFamily

            width: 100
            labelText: "Температура"
            text: "36.6"
            units: "°C"

        }
    }

    Column {
        anchors.horizontalCenter: root.horizontalCenter
        anchors.verticalCenter: root.verticalCenter
        anchors.verticalCenterOffset: -root.height * 1 / 24
        spacing: 6
        Bar {
            labelColor: root.labelsColor; borderColor: root.gridColor; textColor: root.contentColor; barColor: root.accentColor;
            labelPixelSize: root.labelPixelSize; labelFontFamily: root.labelFontFamily; contentFontFamily: root.contentFontFamily;
            width: 100
            labelText: "Объём насоса"
            units: "%"
            maxValue: 100
            value: 23
        }
        Bar {
            labelColor: root.labelsColor; borderColor: root.gridColor; textColor: root.contentColor; barColor: root.accentColor;
            labelPixelSize: root.labelPixelSize; labelFontFamily: root.labelFontFamily; contentFontFamily: root.contentFontFamily;
            width: 100
            labelText: "Объём мотора"
            units: "%"
            maxValue: 100
            value: 61
        }
    }

    Column {
        anchors.horizontalCenter: root.horizontalCenter
        anchors.verticalCenter: root.verticalCenter
        anchors.horizontalCenterOffset: +root.width * 3 / 8
        anchors.verticalCenterOffset: -root.height * 9 / 24

        spacing: -2

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: root.labelPixelSize
            font.family: labelFontFamily
            color: labelsColor
            text: root.date
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: root.labelPixelSize * 1.9
            font.family: labelFontFamily
            color: labelsColor
            text: root.time
        }
    }

    Row {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: root.width / 4

        Repeater {
            model: [
                {
                    pA: 150, pB: 117,
                    motors: [
                        { name: "1", speed: 110 },
                        { name: "2", speed: 120 },
                    ]
                },
                {
                    pA: 17, pB: 420,
                    motors: [
                        { name: "3", speed: 130 },
                        { name: "4", speed: 140 },
                    ]
                },
            ]

            Rectangle  {
                width: root.width / 3.5
                height: width
                color: "#000"
                Text {
                    color: root.labelsColor; font.family: root.labelFontFamily; font.pixelSize: labelPixelSize; font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.verticalCenterOffset: -130
                    text: "Ось " + (index + 1)
                }
                AngleMeter {
                    anchors.fill: parent
                    tickColor: gridColor
                    tickLabelColor: labelsColor
                    needleColor: "#00000000"
                    needleAccents: [ pressureColorA, pressureColorB ]
                    fontFamily: labelFontFamily
                    minAngle: 90 + 110
                    maxAngle: 90 - 110
                    minValue: 0
                    maxValue: 600
                    step: 100
                    smallTicksPerStep: 2
                    cutRadius: 1 / 2.5
                    values: [ modelData.pA, modelData.pB ]
                    warnings: [
                        { minValue: modelData.pA, maxValue: modelData.pB, color: root.accentColor }
                    ]
                }
                Column {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: -5
                    Text {
                        color: root.labelsColor; font.family: root.labelFontFamily; font.bold: true;
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.pixelSize: labelPixelSize
                        text: "Разница"
                    }
                    Text {
                        color: root.accentColor; font.family: contentFontFamily;
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.pixelSize: parent.parent.height / 8
                        text: modelData.pB - modelData.pA
                    }
                    Text {
                        color: root.accentColor; font.family: root.contentFontFamily;
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.pixelSize: labelPixelSize
                        text: "бар"
                    }
                }
                Row {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.verticalCenterOffset: 50
                    spacing: 20
                    Text {
                        font.family: root.labelFontFamily; font.bold: true;
                        color: root.pressureColorA
                        font.pixelSize: labelPixelSize
                        text: "Давление А"
                    }
                    Text {
                        font.family: root.labelFontFamily; font.bold: true;
                        color: root.pressureColorB
                        font.pixelSize: labelPixelSize
                        text: "Давление Б"
                    }
                }
                Row {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.verticalCenterOffset: 105
                    spacing: 50
                    Repeater {
                        model: modelData.motors
                        TextBox {
                            width: 120
                            labelColor: root.labelsColor
                            contentColor: root.contentColor
                            borderColor: root.gridColor

                            contentPixelSize: 20
                            labelPixelSize: root.labelPixelSize
                            labelFontFamily: root.labelFontFamily
                            contentFontFamily: root.contentFontFamily

                            labelText: "Скорость мотора " + modelData.name
                            text: modelData.speed
                            units: "об/мин"
                        }
                    }
                }
            }
        }
    }

    Column {
        opacity: 0
        anchors.horizontalCenter: root.horizontalCenter
        anchors.verticalCenter: root.verticalCenter
        anchors.verticalCenterOffset: root.height * 3 / 24
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: root.labelPixelSize * (20 / 12)
            font.family: labelFontFamily
            font.bold: true
            color: root.warningRed
            text: "Гидравлика"
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: root.labelPixelSize * (20 / 12)
            font.family: labelFontFamily
            font.bold: true
            color: root.warningRed
            text: "заблокирована"
        }
    }

    Rectangle {
        anchors.horizontalCenter: root.horizontalCenter
        anchors.verticalCenter: root.verticalCenter
        anchors.verticalCenterOffset: root.height * 8 / 24
        height: root.height * 5 / 24
        color: "#00000000"
        width: height
        radius: width / 2
        border.width: 2
        border.color: root.gridColor

        Column {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            spacing: -5
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: root.labelPixelSize
                font.family: labelFontFamily
                font.bold: true
                color: root.labelsColor
                text: "Скорость"
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: root.labelPixelSize * (40 / 12)
                font.family: contentFontFamily
                color: root.pressureColorB
                text: root.speed.toFixed(0)
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: root.labelPixelSize
                font.family: labelFontFamily
                color: root.pressureColorB
                text: "км/час"
            }
        }
    }

    Row {
        anchors.horizontalCenter: root.horizontalCenter
        anchors.verticalCenter: root.verticalCenter
        anchors.verticalCenterOffset: root.height * 15 / 48
        spacing: root.width * 0.17
        Repeater {
            model: 2
            Rectangle {
                color: root.pressureColorB
                width: root.width * 0.4
                height: 1
                radius: 1
                opacity: 0.7
            }
        }
    }

    Column {
        anchors.horizontalCenter: root.horizontalCenter
        anchors.verticalCenter: root.verticalCenter
        anchors.verticalCenterOffset: root.height * 19 / 48
        anchors.horizontalCenterOffset: - root.width * 13 / 48
        spacing: 5

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            color: root.labelsColor; font.family: root.labelFontFamily; font.pixelSize: labelPixelSize; font.bold: true
            text: "Скоростя"
        }

        Row {
            anchors.horizontalCenter: root.horizontalCenter
            spacing: 10
            Bar {
                labelColor: root.labelsColor; borderColor: root.gridColor; textColor: root.contentColor; barColor: root.accentColor;
                labelPixelSize: root.labelPixelSize; labelFontFamily: root.labelFontFamily; contentFontFamily: root.contentFontFamily;
                width: 100
                labelText: "Задание OLC"
                units: "%"
                maxValue: 100
                value: 0
            }
            Bar {
                labelColor: root.labelsColor; borderColor: root.gridColor; textColor: root.contentColor; barColor: root.accentColor;
                labelPixelSize: root.labelPixelSize; labelFontFamily: root.labelFontFamily; contentFontFamily: root.contentFontFamily;
                width: 100
                labelText: "Корректировка CLC"
                units: "%"
                maxValue: 100
                value: 28
            }
            Bar {
                labelColor: root.labelsColor; borderColor: root.gridColor; textColor: root.contentColor; barColor: root.accentColor;
                labelPixelSize: root.labelPixelSize; labelFontFamily: root.labelFontFamily; contentFontFamily: root.contentFontFamily;
                width: 100
                labelText: "Полная"
                units: "%"
                maxValue: 100
                value: 76
            }
        }
    }

    Column {
        anchors.horizontalCenter: root.horizontalCenter
        anchors.verticalCenter: root.verticalCenter
        anchors.verticalCenterOffset: root.height * 19 / 48
        anchors.horizontalCenterOffset: + root.width * 13 / 48
        spacing: 5

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            color: root.labelsColor; font.family: root.labelFontFamily; font.pixelSize: labelPixelSize; font.bold: true
            text: "Время"
        }

        Row {
            anchors.horizontalCenter: root.horizontalCenter
            spacing: 15
            TextBox {
                labelPixelSize: root.labelPixelSize; labelColor: root.labelsColor; labelFontFamily: root.labelFontFamily
                borderColor: root.gridColor; contentColor: root.contentColor; contentFontFamily: root.contentFontFamily
                width: 130
                labelText: "Ускорения"
                text: "0.0"
                units: "сек"
            }
            TextBox {
                labelPixelSize: root.labelPixelSize; labelColor: root.labelsColor; labelFontFamily: root.labelFontFamily
                borderColor: root.gridColor; contentColor: root.contentColor; contentFontFamily: root.contentFontFamily
                width: 130
                labelText: "Замедления"
                text: "0.0"
                units: "сек"
            }
        }
    }

}
