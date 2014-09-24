import QtQuick 1.1
import views 1.0

Rectangle {
    width: 640
    height: 480
    id: rootRect

    property color accentColor: "#ffc000"
    property color regularColor: "#fff"

    property int globalBoxHeight: 21
    property int globalFontHeight: globalBoxHeight - 6

    function getDriveModeLetter(driveModeIndex) {
        switch (driveModeIndex) {
        case -1:
            return ""
        case 0:
            return "П"
        case 1:
            return "М"
        case 2:
            return "Р"
        case 3:
            return "Д"
        case 4:
            return "Т"
        }
    }

    function getTargetKindName(kindId) {
        switch (kindId) {
        case -1:
            return ""
        case 1:
            return "Светофор"
        case 2:
            return "Станция"
        case 3:
            return "Оп. место"
        case 4:
            return "Мост"
        case 5:
            return "Переезд"
        case 6:
            return "Платформа"
        case 7:
            return "Туннель"
        case 8:
            return "Стрелка"
        case 9:
            return "ТКС"
        case 10:
            return "ГПУ САУТ"
        case 11:
            return "Тупик"
        }
    }

    focus: true

    SystemStateView {
        id: stateView
        objectName: "stateView"
    }

    Timer {
        id: inputBlinker
        property bool blink: false
        interval: 400
        running: true
        repeat: true
        onTriggered: blink = !blink
        onRunningChanged: blink = true
    }

    Rectangle {
        id: contentArea
        color: "#000"
        anchors.fill: parent

        // Левый столбец с подписями
        Rectangle {
            id: leftCollumn
            anchors.top: parent.top
            anchors.topMargin: 15
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 15
            width: contentArea.width * (2/7)
            color: "#00000000"

            Column {
                anchors.left: parent.left
                anchors.right: parent.right
                spacing: globalBoxHeight * (3/5)

                // Координата
                VerticalLabeledParameterBox {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    accentColor: rootRect.accentColor
                    regularColor: rootRect.regularColor
                    labelText: "КООРДИНАТА"
                    boxHeight: globalBoxHeight
                    fontHeight: globalFontHeight
                    text: "128км 7пк 23м"
                }

                // Номер пути
                HorizontalLabeledParameterBox {
                    labelText: "ПУТЬ:"
                    text: "7"
                    boxHeight: globalBoxHeight
                    fontHeight: globalFontHeight
                    labelWidth: parent.width * 2.0 / 3.0
                    accentColor: rootRect.accentColor
                    regularColor: rootRect.regularColor
                    anchors.left: parent.left
                    anchors.right: parent.right
                }


                // Частота
                Column {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: accentColor
                        font.pixelSize: globalFontHeight
                        font.family: "Calibri"
                        text: "ЧАСТОТА"
                    }
                    // Индикатор частоты
                    Row {
                        id: frequncyIndicator
                        anchors.left: parent.left
                        anchors.right: parent.right
                        Repeater {
                            model: [ 25, 50, 75 ]
                            Indicator {
                                text: modelData + " Гц"
                                isActive: modelData == 50
                                boxHeight: globalBoxHeight
                                fontHeight: globalFontHeight
                                width: frequncyIndicator.width / 3.0
                                accentColor: rootRect.accentColor
                                textColor: "#80ffffff"
                            }
                        }
                    }
                }

                // Часы
                Rectangle {
                    color: "#00000000"
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: 80
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        text: "22:35:18"
                        color: "#95b3d7"
                        font.pixelSize: globalFontHeight * 2
                        font.family: "Calibri"
                    }
                }

                // Давления
                Column {
                    anchors.left: parent.left
                    anchors.right: parent.right

                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: accentColor
                        font.pixelSize: globalFontHeight
                        font.family: "Calibri"
                        text: "ДАВЛЕНИЕ (МПа)"
                    }
                    Row {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        VerticalLabeledParameterBox {
                            labelText: "ТЦ"
                            text: "0,15"
                            width: parent.width / 3.0
                            boxHeight: globalBoxHeight
                            fontHeight: globalFontHeight
                            accentColor: rootRect.accentColor
                            regularColor: rootRect.regularColor
                        }
                        VerticalLabeledParameterBox {
                            labelText: "ТМ"
                            text: "0,51"
                            width: parent.width / 3.0
                            boxHeight: globalBoxHeight
                            fontHeight: globalFontHeight
                            accentColor: rootRect.accentColor
                            regularColor: rootRect.regularColor
                        }
                        VerticalLabeledParameterBox {
                            labelText: "УР"
                            text: "0,50"
                            width: parent.width / 3.0
                            boxHeight: globalBoxHeight
                            fontHeight: globalFontHeight
                            accentColor: rootRect.accentColor
                            regularColor: rootRect.regularColor
                        }
                    }
                }

                // Ускорение
                HorizontalLabeledParameterBox {
                    labelText: "УСКОРЕНИЕ:"
                    text: "-0,15"
                    boxHeight: globalBoxHeight
                    fontHeight: globalFontHeight
                    labelWidth: parent.width * 2.0 / 3.0
                    accentColor: rootRect.accentColor
                    regularColor: rootRect.regularColor
                    anchors.left: parent.left
                    anchors.right: parent.right
                }

                // Коэффициент торможения
                HorizontalLabeledParameterBox {
                    labelText: "КОЭФ. ТОРМ.:"
                    text: "0,32"
                    boxHeight: globalBoxHeight
                    fontHeight: globalFontHeight
                    labelWidth: parent.width * 2.0 / 3.0
                    accentColor: rootRect.accentColor
                    regularColor: rootRect.regularColor
                    anchors.left: parent.left
                    anchors.right: parent.right
                }
            }
        }

        Rectangle {
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 15

            color: "#00000000"
            height: bottomPanel.height

            // Нижняя панель
            Column {
                id: bottomPanel
                anchors.left: parent.left
                anchors.right: parent.right

                // Строка статуса
                ParameterBox {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    borderColor: accentColor
                    textColor: rootRect.regularColor
                    text: "К777"
                    boxHeight: globalBoxHeight
                    fontHeight: globalFontHeight
                }
            }
        }

        // Спидометр с треуольниками движения
        Rectangle {
            anchors.left: leftCollumn.right
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            color: "#00000000"

            Speedometer {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                fontHeight: globalFontHeight
                width: rootRect.width * (6/13)
                height: width

                speed: stateView.Speed;
                speedRestriction: stateView.SpeedRestriction;
                maxSpeed: 300 //20 * Math.ceil(stateView.DesignSpeed * 1.35 / 20);

                speedWarningLimit: 3
                onSpeedWarningPoolsed: stateView.SpeedWarningFlash()
            }
        }
    }
}
