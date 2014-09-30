import QtQuick 1.1
import views 1.0

Rectangle {
    width: 640
    height: 480
    id: rootRect

    property color accentColor: "#ffc000"
    property color regularColor: "#fff"
    property color boxColor: "#70000000"

    property int globalBoxHeight: rootRect.height / 23
    property int globalFontHeight: globalBoxHeight - 6
    property int globalSpacing: globalBoxHeight / 2

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

    Image {
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        source: "Slices/Background.png"
    }

    Rectangle {
        id: contentArea
        color: "#40000000"
        anchors.fill: parent

        // Левый столбец с подписями
        Rectangle {
            id: leftColumn
            anchors.top: parent.top
            anchors.topMargin: globalSpacing
            anchors.left: parent.left
            anchors.leftMargin: globalSpacing
            anchors.bottom: parent.bottom
            anchors.bottomMargin: globalSpacing
            width: contentArea.width * (2/7)
            color: "#00000000"

            property int labelsColumnWidth: width * (2/3)

            Column {
                anchors.left: parent.left
                anchors.right: parent.right
                spacing: globalSpacing

                // Координата
                VerticalLabeledParameterBox {
                    id: ordinateBox
                    anchors.left: parent.left
                    anchors.right: parent.right
                    accentColor: rootRect.accentColor
                    regularColor: rootRect.regularColor
                    backgroundColor: boxColor
                    labelText: "КООРДИНАТА"
                    boxHeight: globalBoxHeight
                    fontHeight: globalFontHeight
                    text: ((stateView.Ordinate / 1000) - ((stateView.Ordinate / 1000) % 1) + 1) + "км " +
                          (((stateView.Ordinate % 1000 ) / 100) - (((stateView.Ordinate % 1000 ) / 100) % 1) + 1) + "пк " +
                          ((stateView.Ordinate % 100 - stateView.Ordinate % 10) / 10).toFixed(0) +
                          (stateView.Ordinate % 10).toString() + "м"
                }

                // Номер пути
                HorizontalLabeledParameterBox {
                    labelText: "ПУТЬ:"
                    text: stateView.TrackNumber
                    boxHeight: globalBoxHeight
                    fontHeight: globalFontHeight
                    labelWidth: leftColumn.labelsColumnWidth
                    accentColor: rootRect.accentColor
                    regularColor: rootRect.regularColor
                    backgroundColor: boxColor
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
                        font.family: "URW Gothic L"
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
                                isActive: modelData == stateView.AlsnFreqFact
                                boxHeight: globalBoxHeight
                                fontHeight: globalFontHeight
                                width: frequncyIndicator.width / 3.0
                                accentColor: rootRect.accentColor
                                backgroundColor: boxColor
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
                    height: globalBoxHeight * 4
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        text: stateView.Time
                        color: "#95b3d7"
                        font.pixelSize: globalFontHeight * 2
                        font.family: "URW Gothic L"
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
                        font.family: "URW Gothic L"
                        text: "ДАВЛЕНИЕ (МПа)"
                    }
                    Row {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        VerticalLabeledParameterBox {
                            labelText: "ТЦ"
                            text: stateView.PressureTC
                            width: parent.width / 3.0
                            boxHeight: globalBoxHeight
                            fontHeight: globalFontHeight
                            accentColor: rootRect.accentColor
                            regularColor: rootRect.regularColor
                            backgroundColor: boxColor
                        }
                        VerticalLabeledParameterBox {
                            labelText: "ТМ"
                            text: stateView.PressureTM
                            width: parent.width / 3.0
                            boxHeight: globalBoxHeight
                            fontHeight: globalFontHeight
                            accentColor: rootRect.accentColor
                            regularColor: rootRect.regularColor
                            backgroundColor: boxColor
                        }
                        VerticalLabeledParameterBox {
                            labelText: "УР"
                            text: stateView.PressureUR
                            width: parent.width / 3.0
                            boxHeight: globalBoxHeight
                            fontHeight: globalFontHeight
                            accentColor: rootRect.accentColor
                            regularColor: rootRect.regularColor
                            backgroundColor: boxColor
                        }
                    }
                }

                // Ускорение
                HorizontalLabeledParameterBox {
                    labelText: "УСКОРЕНИЕ:"
                    text: stateView.Acceleration
                    boxHeight: globalBoxHeight
                    fontHeight: globalFontHeight
                    labelWidth: leftColumn.labelsColumnWidth
                    accentColor: rootRect.accentColor
                    regularColor: rootRect.regularColor
                    backgroundColor: boxColor
                    anchors.left: parent.left
                    anchors.right: parent.right
                }

                // Коэффициент торможения
                HorizontalLabeledParameterBox {
                    labelText: "КОЭФ. ТОРМ.:"
                    text: stateView.BrakingCoefficient
                    boxHeight: globalBoxHeight
                    fontHeight: globalFontHeight
                    labelWidth: leftColumn.labelsColumnWidth
                    accentColor: rootRect.accentColor
                    regularColor: rootRect.regularColor
                    backgroundColor: boxColor
                    anchors.left: parent.left
                    anchors.right: parent.right
                }
            }
        }

        // Верхняя строка
        Rectangle {
            id: topRow
            anchors.left: leftColumn.right
            anchors.leftMargin: globalSpacing
            anchors.right: contentArea.right
            anchors.rightMargin: globalSpacing
            anchors.top: contentArea.top
            anchors.topMargin: globalSpacing
            height: ordinateBox.height
            color: "#00000000"



            // Координата
            VerticalLabeledParameterBox {
                anchors.left: parent.left
                anchors.right: topIconsRow.left
                anchors.rightMargin: globalSpacing
                accentColor: rootRect.accentColor
                regularColor: rootRect.regularColor
                backgroundColor: boxColor
                labelText: "СТАНЦИЯ"
                boxHeight: globalBoxHeight
                fontHeight: globalFontHeight
                text: stateView.NextStatinName
            }

            // Строка иконок в верхнем ряду
            Row {
                id: topIconsRow
                anchors.right: parent.right
                spacing: globalSpacing

                Row {
                    anchors.bottom: parent.bottom
                    IconBox {
                        borderColor: accentColor
                        backgroundColor: boxColor
                        boxHeight: globalBoxHeight
                        width: height
                    }
                    IconBox {
                        borderColor: accentColor
                        backgroundColor: boxColor
                        //backgroundColor: accentColor
                        boxHeight: globalBoxHeight
                        width: height
                        iconSource: stateView.IsRegistrationTapeActive
                                    ? "Slices/Registration-Type.png"
                                    : ""
                    }
                }

                // Режим движения (переключатель РМП)
                Column {
                    id: rmpSwitch

                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: accentColor
                        font.pixelSize: globalFontHeight
                        font.family: "URW Gothic L"
                        text: "РЕЖИМ"
                    }

                    Row {
                        Repeater {
                            model: [ "П", "М", "Р" ]
                            Indicator {
                                text: modelData
                                isActive: modelData == getDriveModeLetter(stateView.DriveModeFact)
                                boxHeight: globalBoxHeight
                                fontHeight: globalFontHeight
                                width: globalBoxHeight
                                accentColor: rootRect.accentColor
                                backgroundColor: boxColor
                                textColor: "#80ffffff"
                            }
                        }
                    }
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
                spacing: globalSpacing

                HorizontalLabeledParameterBox {
                    labelText: "ДО ЦЕЛИ САУТ:"
                    text: stateView.SautTargetDistance + "м"
                    boxHeight: globalBoxHeight
                    fontHeight: globalFontHeight
                    labelWidth: leftColumn.labelsColumnWidth
                    accentColor: rootRect.accentColor
                    regularColor: rootRect.regularColor
                    backgroundColor: boxColor
                    anchors.left: parent.left
                    width: leftColumn.width
                }

                HorizontalLabeledParameterBox {
                    labelText: "ЦЕЛЬ КЛУБ:"
                    text: (stateView.NextTargetKind > 0 && stateView.NextTargetDistance > 0) ?
                              getTargetKindName(stateView.NextTargetKind) + " " +
                              stateView.NextTargetName +
                              "через " + stateView.NextTargetDistance + "м"
                              : "нет данных о цели" ;
                    boxHeight: globalBoxHeight
                    fontHeight: globalFontHeight
                    labelWidth: leftColumn.labelsColumnWidth
                    accentColor: rootRect.accentColor
                    regularColor: rootRect.regularColor
                    backgroundColor: boxColor
                    anchors.left: parent.left
                    anchors.right: parent.right
                }

                // Строка статуса
                ParameterBox {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    borderColor: accentColor
                    textColor: rootRect.regularColor
                    backgroundColor: boxColor
                    text: "К777"
                    boxHeight: globalBoxHeight
                    fontHeight: globalFontHeight
                }
            }
        }

        // Спидометр с треуольниками движения
        Rectangle {
            anchors.left: leftColumn.right
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
