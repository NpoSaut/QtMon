import QtQuick 1.1
import views 1.0

Rectangle {
    width: 800
    height: 480
    id: rootRect

    property int pageNum: 0

    property double maxSpeed: 60

    function switchPage() {
        pageNum = 1 - pageNum
    }

    property int guryanovId: 0

    function refreshAlsnState()
    {
        alsnSelector.state = "alsn0"
        if (alsnSelectorMarker.y < 0.25 * (alsnSelector.height - alsnSelectorMarker.height))
        {
            alsnSelector.state = "alsn25"
        }
        else if (alsnSelectorMarker.y < 0.75 * (alsnSelector.height - alsnSelectorMarker.height))
        {
            alsnSelector.state = "alsn50"
        }
        else
        {
            alsnSelector.state = "alsn75"
        }
    }

    property int mouseDragStartY: -1
    function swipePressed(mouseY)
    {
        mouseDragStartY = mouseY
    }
    function swipeReleased(mouseY)
    {
        if (mouseDragStartY > 0)
        {
            if (mouseDragStartY - mouseY > 50) rootRect.state = "page2";
            else if (mouseY - mouseDragStartY > 50) rootRect.state = "page1";
            else return;
        }
    }


    function getDriveModeLetter(driveModeIndex)
    {
        switch (driveModeIndex)
        {
            case -1: return "";
            case 0: return "П";
            case 1: return "М";
            case 2: return "Р";
            case 3: return "Д";
            case 4: return "Т";
        }
    }

    focus: true

    // Указывает, что нажата кнопка-модификатор альтернативного режима клавиш F2-F3
    property bool altMode: false


    Keys.onPressed: {
        // Переключение частоты АЛСН
        if (!inputMode)
        {
        	if (!altMode && event.key == Qt.Key_F1) {
	            // Send CAN requset to change ALSN freq

                // Emulation
                if (stateView.AlsnFreqTarget == 25 )
                    stateView.AlsnFreqTarget = 50;
                else if ( stateView.AlsnFreqTarget == 50 )
                    stateView.AlsnFreqTarget = 75;
                else if ( stateView.AlsnFreqTarget == 75 )
                    stateView.AlsnFreqTarget = 25;
                else
                    stateView.AlsnFreqTarget = 25;
	        }
    	    else if (altMode && event.key == Qt.Key_F1) {
	            stateView.AutolockTypeTarget = (stateView.AutolockTypeTarget + 1) % 3
            }
            // Кнопка смены режима движения (РМП)
            else if (!altMode && event.key == Qt.Key_F2) {
                stateView.ChangeDrivemodeButtonPressed();
            }
            // Alt: Отмена Красного
            else if (altMode && event.key == Qt.Key_F2) {
                stateView.DisableRedButtonPressed();
            }
            // Страница дорожного режима
            else if (!altMode && event.key == Qt.Key_F3) {
                switchPage();
            }
            // Alt: пустой
            else if (altMode && event.key == Qt.Key_F3) {
                inputMode = true
            }
            // Включение альтернативного режим клавиш
            else if (event.key == Qt.Key_F4) {
                altMode = true;

                var input = inputPositions
                for (var i = 0; i < inputPositions.length; i++)
                    input[input.length - i - 1] = Math.floor(guryanovId / Math.pow(10, i)) % 10;
                inputPositions = input;
            }
        }
        else
        {
            if (event.key == Qt.Key_F1)
            {
                var input = inputPositions
                input[inputCursorIndex] = (input[inputCursorIndex] + 1) % 10
                inputPositions = input;
            }
            if (event.key == Qt.Key_F2)
            {
                inputCursorIndex++;
                if (inputCursorIndex >= inputPositions.length) inputCursorIndex = 0;
            }
            if (event.key == Qt.Key_F3)
            {
                inputCursorIndex--;
                if (inputCursorIndex < 0) inputCursorIndex = inputPositions.length-1;
            }
            if (event.key == Qt.Key_F4)
            {
                inputMode = false
                guryanovId = 0;
                for (var i = 0; i < inputPositions.length; i++)
                    guryanovId += Math.pow(10, i) * inputPositions[inputPositions.length - i - 1];
                driverIdSegments = inputPositions;
            }
        }
    }

    Keys.onReleased: {
        // Выключение альтернативного режима клавиш
        if (event.key == Qt.Key_F4) {
            altMode = false;
        }
        // Отпускание кнопки РМП
        else if (!altMode && event.key == Qt.Key_F2) {
            stateView.ChangeDrivemodeButtonReleased();
        }
        // Alt: Отмена Красного
        else if (altMode && event.key == Qt.Key_F2) {
            stateView.DisableRedButtonReleased();
        }
        // Alt: пустой
        else if (altMode && event.key == Qt.Key_F3) {
        }

    }


    SystemStateView {
        id: stateView
        objectName: "stateView"

        onDriveModeFactChanged: {
            if (stateView.DriveModeFact == stateView.DriveModeTarget)
                pageNum = getDriveModeLetter(stateView.DriveModeFact) == "Т" ? 1 : 0
        }
    }

    states: [
        State {
            name: "page1"
            when: pageNum == 0
            PropertyChanges { target: pagesContainer; y: 0 }

            PropertyChanges { target: speedBox; anchors.bottomMargin: -100 }
            PropertyChanges { target: graduateBar; opacity: 0 }
        },
        State {
            name: "page2"
            when: pageNum == 1
            PropertyChanges { target: pagesContainer; y: -1 * pagesArea.height }
        }
    ]

    transitions: Transition {
        NumberAnimation { target: pagesContainer; properties: "y"; easing.type: Easing.InOutQuad; duration: 500 }

        NumberAnimation { target: speedBox; properties: "anchors.bottomMargin"; easing.type: Easing.OutQuad; duration: 300 }
        NumberAnimation { target: graduateBar; properties: "opacity"; easing.type: Easing.OutQuad; duration: 300 }
    }

    property bool inputMode: false
    property int inputCursorIndex: 0
    property variant inputPositions: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0]
//    property variant inputPositions: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    property variant driverIdSegments: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

    Rectangle {
        id: pagesArea
        color: "#00000000"
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.rightMargin: 149
        anchors.left: parent.left
        anchors.leftMargin: 151

        Column {
            id: pagesContainer
            anchors.right: parent.right
            anchors.left: parent.left
            Rectangle {
                id: page1container
                height: pagesArea.height
                color: "#00000000"
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.leftMargin: 0
                Image {
                    source: "Slices/Background.png"
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                }

            Row {
                anchors.left: parent.left
                anchors.leftMargin: 14
                anchors.topMargin: 23
                anchors.top: parent.top
                spacing: 70

                Column {
                    spacing: 40
                    width: 123

                    // Координата
                   Column {
                       anchors.left: parent.left
                       anchors.right: parent.right
                       Text {
                           anchors.horizontalCenter: parent.horizontalCenter

                           text: qsTr("ОРДИНАТА")
                           color: "#ffffff00"
                           font.pixelSize: 14
                           font.family: "URW Gothic L"
                       }
                       Rectangle {
                           color: "#20000000"
                           anchors.left: parent.left
                           anchors.right: parent.right
                           border.color: "#ffffff00"
                           height: 20
                           Text {
                               anchors.horizontalCenter: parent.horizontalCenter
                               anchors.verticalCenter: parent.verticalCenter
                               text: ((stateView.Milage / 1000) - ((stateView.Milage / 1000) % 1)) + "км " +
                                     (((stateView.Milage % 1000 ) / 100) - (((stateView.Milage % 1000 ) / 100) % 1)) + "пк " +
                                     (stateView.Milage % 100).toString() + "м"
                               //text: stateView.Speed
                               color: "#ffffffff"
                               font.pixelSize: 14
                               font.family: "URW Gothic L"
                           }
                       }
                   }

                    // № ПУТИ
                   Column {
                       anchors.left: parent.left
                       anchors.right: parent.right
                       Text {
                           anchors.horizontalCenter: parent.horizontalCenter

                           text: qsTr("№ ПУТИ")
                           color: "#ffffff00"
                           font.pixelSize: 14
                           font.family: "URW Gothic L"
                       }
                       Rectangle {
                           color: "#20000000"
                           anchors.left: parent.left
                           anchors.right: parent.right
                           border.color: "#ffffff00"
                           height: 20
                           Text {
                               anchors.horizontalCenter: parent.horizontalCenter
                               anchors.verticalCenter: parent.verticalCenter
                               text: qsTr("--")
                               color: "#ffffffff"
                               font.pixelSize: 14
                               font.family: "URW Gothic L"
                           }
                       }
                   }

                   // УСКОРЕНИЕ
                  Column {
                      anchors.left: parent.left
                      anchors.right: parent.right
                      Text {
                          anchors.horizontalCenter: parent.horizontalCenter

                          text: qsTr("УСКОРЕНИЕ")
                          color: "#ffffff00"
                          font.pixelSize: 14
                          font.family: "URW Gothic L"
                      }
                      Rectangle {
                          color: "#20000000"
                          anchors.left: parent.left
                          anchors.right: parent.right
                          border.color: "#ffffff00"
                          height: 20
                          Text {
                              anchors.horizontalCenter: parent.horizontalCenter
                              anchors.verticalCenter: parent.verticalCenter
                              //text: qsTr("0.15")
                              text: stateView.Acceleration.toFixed(2)
                              color: "#ffffffff"
                              font.pixelSize: 14
                              font.family: "URW Gothic L"
                          }
                      }
                  }

                  // ТЦ
                 Column {
                     anchors.left: parent.left
                     anchors.right: parent.right
                     Text {
                         anchors.horizontalCenter: parent.horizontalCenter

                         text: qsTr("ТЦ")
                         color: "#ffffff00"
                         font.pixelSize: 14
                         font.family: "URW Gothic L"
                     }
                     Rectangle {
                         color: "#20000000"
                         anchors.left: parent.left
                         anchors.right: parent.right
                         border.color: "#ffffff00"
                         height: 20
                         Text {
                             anchors.horizontalCenter: parent.horizontalCenter
                             anchors.verticalCenter: parent.verticalCenter
                             text: qsTr(stateView.PressureTC + " МПа")
                             color: "#ffffffff"
                             font.pixelSize: 14
                             font.family: "URW Gothic L"
                         }
                     }
                 }

                 // ТМ
                Column {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter

                        text: qsTr("ТМ")
                        color: "#ffffff00"
                        font.pixelSize: 14
                        font.family: "URW Gothic L"
                    }
                    Rectangle {
                        color: "#20000000"
                        anchors.left: parent.left
                        anchors.right: parent.right
                        border.color: "#ffffff00"
                        height: 20
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                            text: qsTr(stateView.PressureTM + " МПа")
                            color: "#ffffffff"
                            font.pixelSize: 14
                            font.family: "URW Gothic L"
                        }
                    }
                }

                }

                // Время
               Column {
                   width: 100

                   //anchors.left: parent.left
                   //anchors.right: parent.right
                   Text {
                       anchors.horizontalCenter: parent.horizontalCenter

                       text: qsTr("ВРЕМЯ")
                       color: "#ffffff00"
                       font.pixelSize: 14
                       font.family: "URW Gothic L"
                   }
                   Rectangle {
                       color: "#20000000"
                       anchors.left: parent.left
                       anchors.right: parent.right
                       border.color: "#ffffff00"
                       height: 20
                       Text {
                           anchors.horizontalCenter: parent.horizontalCenter
                           anchors.verticalCenter: parent.verticalCenter
                           //text: qsTr("12:28:45")
                           text: stateView.Time


                           color: "#ffffffff"
                           font.pixelSize: 14
                           font.family: "URW Gothic L"
                       }
                   }
               }

               Row {
                   anchors.top: parent.top
                   anchors.topMargin: 18

                   // Буква режима движения
                   Rectangle {
                       color: "#20000000"
                       border.color: "#ffffff00"
                       width: 20
                       height: 20
                       Text {
                           anchors.horizontalCenter: parent.horizontalCenter
                           anchors.verticalCenter: parent.verticalCenter
                           text: getDriveModeLetter(stateView.DriveModeFact)

                           color: "#ffffffff"
                           font.pixelSize: 14
                           font.family: "URW Gothic L"
                       }
                   }

                   // Яйца
                   Rectangle {
                       color: "#20000000"
                       border.color: "#ffffff00"
                       width: 21
                       height: 20
                       Image {
                           anchors.horizontalCenter: parent.horizontalCenter
                           anchors.verticalCenter: parent.verticalCenter
                           source: "Slices/Registration-Type.png"
                           opacity: stateView.IsRegistrationTapeActive ? 1 : 0
                       }
                   }

                   // Сигнал с небес (достоверность GPS)
                   Rectangle {
                       color: "#20000000"
                       border.color: "#ffffff00"
                       width: 21
                       height: 20
                       Image {
                           anchors.horizontalCenter: parent.horizontalCenter
                           anchors.verticalCenter: parent.verticalCenter
                           source: "Slices/icon-gps-valid.png"
                           opacity: stateView.SpeedFromSky >= 0 ? 1 : 0
                       }
                   }
               }

            }

            // Спидометр
            Rectangle {
                id: speedometer
                anchors.right: parent.right
                anchors.rightMargin: 30
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 10
                color: "#00000000"
                //border.color: "#60ffa000"
                //border.width: 1
                //clip: true
                width: 300
                height: width

                // Количество засечек
                property int tickCount: maxSpeed / 5

                property double minAngle: 1.25 * Math.PI
                property double maxAngle: -0.25 * Math.PI
                property double anglePerKph: (minAngle - maxAngle)/maxSpeed

                property double tableRadius: width / 2

                // Обрезалка
                Rectangle {
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right

                    property double filedWidth: 15

                    anchors.topMargin: -filedWidth
                    anchors.leftMargin: -filedWidth
                    anchors.rightMargin: -filedWidth

                    height: (1 - Math.sin(parent.minAngle)) * parent.tableRadius + filedWidth - 1

                    color: "#00000000"
                    clip: true

                    // Дуга шкалы спидометра
                    Rectangle {
                        color: "#00000000"
                        border.color: "#fff"
                        border.width: 3

                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.right: parent.right

                        property double unFiledWidth: parent.filedWidth + border.width/2
                        anchors.topMargin: unFiledWidth
                        anchors.leftMargin: unFiledWidth
                        anchors.rightMargin: unFiledWidth

                        height: width
                        radius: width / 2
                    }
                }

                // Насечки на шкале
                Repeater {
                    model: speedometer.tickCount + 1
                    Rectangle {

                        property double kph: index * (maxSpeed / speedometer.tickCount)
                        property double angle: speedometer.minAngle - kph * speedometer.anglePerKph

                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenterOffset: - parent.tableRadius * Math.sin(angle)
                        anchors.horizontalCenterOffset: parent.tableRadius * Math.cos(angle)


                        Rectangle {
                            width: 10
                            height: 3

                            rotation: -angle * 180 / Math.PI
                            smooth: true

                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.verticalCenterOffset: 20 * Math.sin(parent.angle)
                            anchors.horizontalCenterOffset: - 20 * Math.cos(parent.angle)
                            text: parent.kph
                            color: "#ffffffff"

                            font.pixelSize: 16
                            font.family: "URW Gothic L"
                        }
                    }
                }

                // Стрелка спидометра
                Image {
                    source: stateView.SpeedIsValid ?
                                "Slices/Needle-Speed.png" :
                                "Slices/Needle-Speed-Invalid.png"

                    rotation: 180 - (speedometer.minAngle - speedometer.anglePerKph * stateView.Speed) * 180 / Math.PI
                    smooth: true

                    transformOrigin: Item.Right

                    anchors.right: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }


                // Стрелка целевой скорости
                Rectangle {
                    transformOrigin: Item.Right

                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter

                    property double r: parent.tableRadius + 4
                    property double angle: speedometer.minAngle - stateView.TargetSpeed * speedometer.anglePerKph

                    anchors.verticalCenterOffset: - r * Math.sin(angle)
                    anchors.horizontalCenterOffset: r * Math.cos(angle)

                    rotation: 180 - angle * 180 / Math.PI

                    Image {
                        source: "Slices/Needle-Target-Speed.png"
                        smooth: true

                        anchors.right: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                // Стрелка ограничения скорости
                Rectangle {
                    transformOrigin: Item.Right

                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter

                    property double r: parent.tableRadius + 4
                    property double angle: speedometer.minAngle - stateView.SpeedRestriction * speedometer.anglePerKph

                    anchors.verticalCenterOffset: - r * Math.sin(angle)
                    anchors.horizontalCenterOffset: r * Math.cos(angle)

                    rotation: 180 - angle * 180 / Math.PI

                    Image {
                        source: "Slices/Needle-Restriction.png"
                        smooth: true

                        anchors.right: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                // Числа скорости и ограничения в кругляше в центре
                Rectangle {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter

                    width: 80
                    height: width
                    radius: width / 2

                    color: "#4999c9"

                    // Индикатор отсутствия тяги вокруг кругляша скорости
                    Rectangle {
                        property int thick: 3
                        z: parent.z - 5
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        color: "#fff"
                        width: parent.width + thick*2
                        height: width
                        radius: width/2
                        visible: !stateView.IsTractionOn
                    }

                    // Текущая скорость
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter

                        text: stateView.SpeedIsValid ? stateView.Speed.toFixed() : "N/A"
                        color: "#fff"

                        font.pixelSize: 35
                        font.family: "URW Gothic L"
                        font.bold: true
                    }

                    // Ограничение скорости
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.verticalCenterOffset: 65

                        text: stateView.SpeedRestriction.toFixed()
                        color: "#c94949"

                        font.pixelSize: 35
                        font.family: "URW Gothic L"
                        font.bold: true
                    }

                }
            }

            // Треугольники направления движения
            Row {
                spacing: 30
                anchors.horizontalCenter: speedometer.horizontalCenter
                anchors.bottom: speedometer.bottom
                anchors.bottomMargin: 30

                // Направление вперёд
                Image {
                    source: stateView.Direction == 1 ?
                                "Slices/Direction-Forward.png" :
                                "Slices/Direction-None.png";
                }
                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    height: 16
                    width: height
                    radius: height / 2
                    color: "#00000000"

                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        text: "STOP"
                        color: "#fff"
                        font.pixelSize: 16
                        font.bold: true
                        visible: false
                    }
                }

                // Направление назад
                Image {
                    source: stateView.Direction == -1 ?
                                "Slices/Direction-Back.png" :
                                "Slices/Direction-None.png";
                }
            }

            Rectangle {
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 45
                anchors.left: parent.left
                anchors.leftMargin: 30
                anchors.right: parent.right
                anchors.rightMargin: 30
                height: 50

                opacity: warningLabel.text != "" ? 1 : 0
                Behavior on opacity { PropertyAnimation { duration: 150 } }

                radius: 5
                color: "#303030"
                border.color: "#222"
                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.verticalCenterOffset: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.horizontalCenterOffset: 1
                    height: parent.height
                    width: parent.width

                    radius: parent.radius
                    z: parent.z - 1
                    color: "#00000000"
                    border.color: "#80606060"
                }

                Text {
                    id: warningLabel
                    color: "#ff6200"
                    font.family: "URW Gothic L";
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 36

                    text:
                    {
                        if (stateView.WarningText != "") return stateView.WarningText
                        if (!stateView.IsEpvReady) return "Система отключена"
                        if (stateView.IsEpvReleased) return "Экстренное торможение"
                        if (stateView.InfoText != "") return stateView.InfoText
                        return "";
                    }

                    property bool isActive: false;
                    opacity: 1.0 * isActive
                    Behavior on opacity { PropertyAnimation { duration: 70 } }

                    Timer {
                        interval: 400
                        running: parent.text != "" || parent.isActive
                        repeat: true
                        onTriggered: parent.isActive = !parent.isActive
                    }
                }
            }

            // Информационная строка
            Rectangle {
                color: "#20000000"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.leftMargin: 10
                border.color: "#ffffff00"
                //width: 100
                height: 25
            }



            }

            Rectangle {
                id: page2container
                height: pagesArea.height
                anchors.right: parent.right
                anchors.left: parent.left
                clip: true

                Rectangle {
                    id: mapContainer
                    anchors.fill: parent

                    function getHorizontalIndex(Longitude)
                    {
                        return Math.floor( (Longitude + 180) / 360 * (1<<13) ) ;
                    }
                    function getVerticalIndex(Latitude)
                    {
                        return Math.floor((1 - Math.log(Math.tan(Math.PI * Latitude / 180) + 1 / Math.cos(Math.PI * Latitude / 180)) / Math.PI) / 2 * (1<<13));
                    }
                    function getLongitude(horizontalIndex)
                    {
                        return horizontalIndex / Math.pow(2.0, 13) * 360.0 - 180;
                    }
                    function getLatitude(verticalIndex)
                    {
                        var n = Math.PI - 2.0 * Math.PI * verticalIndex / Math.pow(2.0, 13);
                        return 180.0 / Math.PI * Math.atan(0.5 * (Math.exp(n) - Math.exp(-n)));
                    }

                    property int currentHorizontalIndex: getHorizontalIndex(stateView.Longitude)
                    property int currentVerticalIndex: getVerticalIndex(stateView.Latitude)

                    property double horizontalDensity: 256/(getLongitude(currentHorizontalIndex + 1) - getLongitude(currentHorizontalIndex))
                    property double verticalDensity: 256/(getLatitude(currentVerticalIndex + 1) - getLatitude(currentVerticalIndex))


                    Repeater {
                        model:9
                        Image {
                            property int relativeHorizontalIndex: (index % 3) - 1
                            property int relativeVerticalIndex: (Math.floor(index / 3)) - 1

                            property int horizontalIndex: mapContainer.currentHorizontalIndex + relativeHorizontalIndex
                            property int verticalIndex: mapContainer.currentVerticalIndex + relativeVerticalIndex

                            property double leftCoordinate: mapContainer.getLongitude(horizontalIndex)
                            property double topCoordinate: mapContainer.getLatitude(verticalIndex)

                            x: (leftCoordinate - stateView.Longitude)*mapContainer.horizontalDensity + page1container.width/2
                            y: (topCoordinate - stateView.Latitude)*mapContainer.verticalDensity + page1container.height/2

                            source: "../../MapTiles/" + horizontalIndex + "-" + verticalIndex + ".png"
                            //asynchronous: true

                            Rectangle
                            {
                                color: "#00000000"
                                border.color: "#ff00f7"
                                anchors.fill: parent
                                opacity: 0.1
                            }

                            //Behavior on x { SmoothedAnimation { duration: 1000 } }
                            //Behavior on y { SmoothedAnimation { duration: 1000 } }
                        }
                    }


                }

                Image {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "Slices/Cross.png"
                }


                Rectangle {
                    id: hintBox

                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: -10
                    height: background.height
                    width: background.width

                    color: "#00000000"
                    anchors.left: parent.left
                    anchors.leftMargin: 15

                    Image {
                        id: background
                        source: "Slices/hint.png"
                    }

                    Text {
                        text: stateView.Time;

                        anchors.top: parent.top
                        anchors.topMargin: 3
                        anchors.left: parent.left
                        anchors.leftMargin: 16

                        font.family: "URW Gothic L"; font.pixelSize: 14;
                        color: "#2d2d2d";
                    }

                    Text {
                        id: hintBoxMilageKm
                        text: (stateView.Milage/1000).toFixed(1) + qsTr(" км")

                        anchors.top: parent.top
                        anchors.topMargin: 3
                        anchors.right: parent.right
                        anchors.rightMargin: 16

                        font.family: "URW Gothic L"; font.pixelSize: 14
                        color: "#2d2d2d";
                    }
                }
            }
        }
        MouseArea {
            enabled: false
            anchors.fill: parent
            onPressed: swipePressed(mouseY)
            onReleased: swipeReleased(mouseY)
        }

    }



    Rectangle {
        id: panelLeft

        width: 151
        height: 480
        color: "#00000000"
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: parent.top

        Image {
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            source: "Slices/Panel-Left.png"
        }

        Image {
            x: -14
            y: 104
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            source: "Slices/Panel-Left-Middle.png"
        }

        Rectangle {
            id: leftBorder
            width: 6
            color: "#4999c9"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.top: parent.top
        }

        Column {
            anchors.fill: parent

            Rectangle {
                id: rightButton1Container
                height: 120
                color: "#00000000"
                anchors.right: parent.right
                anchors.left: parent.left

                Rectangle {
                    anchors.fill: parent
                    color: "#00000000"
                    clip: true


                    Image {
                        id: alsnSwitchBackgroundCircle
                        anchors.right: parent.left
                        anchors.rightMargin: -60
                        anchors.top: parent.top
                        anchors.topMargin: -height/2 + 60

                        fillMode: "Tile"
                        source: "Slices/alsn-switch.png"
                    }


                    Rectangle {
                        id: alsnTextBox
                        color: "#00000000"
                        anchors.left: alsnSwitch.right
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.verticalCenterOffset: -3
                        height: alsnTextBoxText.height + alsnTextBoxLine.height + alsnTextBoxFreq.height
                        width: alsnTextBoxLine.width


                        Text {
                            id: alsnTextBoxText
                            anchors.left: parent.left

                            text: qsTr("АЛСН")
                            color: "#ffdddddd"
                            font.pixelSize: 18
                            font.family: "URW Gothic L"
                            font.bold: true
                        }
                        Rectangle {
                            id: alsnTextBoxLine
                            anchors.left: parent.left
                            anchors.top: alsnTextBoxText.bottom
                            width: 60
                            height: 2
                            color: "#ffdddddd"

                        }
                        Text {
                            id: alsnTextBoxFreq
                            anchors.left: parent.left
                            anchors.top: alsnTextBoxLine.bottom

                            text: qsTr("частота")
                            color: "#ffdddddd"
                            font.pixelSize: 14
                            font.family: "URW Gothic L"
                            font.bold: true
                        }
                    }

                    Rectangle {
                        id: alsnSwitch
                        color: "#00000000"

                        anchors.top: parent.top
                        anchors.topMargin: -height/2 + 60
                        anchors.right: parent.left
                        anchors.rightMargin: -60
                        width: alsnSwitchBackgroundCircle.width
                        height: alsnSwitchBackgroundCircle.height

                        property real radius: 100
                        property real angle: 15
                        property string objColor: "#ddd"
                        property string objHighlightColor: "#f22"

                        Repeater
                        {
                            model: [25, 50, 75]

                            Rectangle {
                                property real myRot: (1 - index) * alsnSwitch.angle
                                property int freq: modelData

                                x: alsnSwitch.width/2 + alsnSwitch.radius * Math.cos(myRot / 180 * Math.PI)
                                y: alsnSwitch.height/2 + alsnSwitch.radius * Math.sin(myRot / 180 * Math.PI)
                                rotation: myRot

                                color: stateView.AlsnFreqFact == freq ? alsnSwitch.objHighlightColor : alsnSwitch.objColor
                                width: 2
                                height: 2
                                smooth: true

                                Text {
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.right: parent.left
                                    anchors.rightMargin: 4

                                    text: parent.freq
                                    font.pixelSize: 14
                                    font.family: "URW Gothic L"
                                    color: alsnSwitch.objColor
                                    smooth: true
                                }
                            }
                        }

                        states: [
                            State {
                                name: "alsn0"
                                when: (stateView.AlsnFreqTarget != 25 && tateView.AlsnFreqTarget != 50 && tateView.AlsnFreqTarget != 75)
                                PropertyChanges { target: alsnSwitch; rotation: -2 * alsnSwitch.angle }
                            },
                            State {
                                name: "alsn25"
                                when: (stateView.AlsnFreqTarget == 25)
                                PropertyChanges { target: alsnSwitch; rotation: -1 * alsnSwitch.angle }
                            },
                            State {
                                name: "alsn50"
                                when: (stateView.AlsnFreqTarget == 50)
                                PropertyChanges { target: alsnSwitch; rotation: 0 * alsnSwitch.angle }
                            },
                            State {
                                name: "alsn75"
                                when: (stateView.AlsnFreqTarget == 75)
                                PropertyChanges { target: alsnSwitch; rotation: +1 * alsnSwitch.angle }
                            }
                        ]

                        transitions: Transition {
                            NumberAnimation { target: alsnSwitch; properties: "rotation"; easing.type: Easing.InOutQuad; duration: 200 }
                        }
                    }


                    Row {
                        id: autolockSelector
                        anchors.horizontalCenter: alsnTextBox.horizontalCenter
                        anchors.horizontalCenterOffset: 3
                        anchors.bottom: alsnTextBox.top
                        anchors.bottomMargin: 16
                        spacing: 4
                        property int itemWidth: 26

                        Repeater {
                            model: ["АБ", "ПАБ", "ЗАБ"]
                            Rectangle {
                                property bool isConfirmed: index == stateView.AutolockTypeFact
                                anchors.verticalCenter: parent.verticalCenter
                                width: autolockSelector.itemWidth
                                height: 14
                                radius: 2
                                color: isConfirmed ? "#ccc" : "#00000000"
                                Text {
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    text: modelData
                                    font.pixelSize: 10
                                    color: parent.isConfirmed ? "#333" : "#ccc"
                                }
                            }
                        }
                    }
                    Rectangle {
                        id: autolockSelectorCursor
                        anchors.top: autolockSelector.bottom
                        anchors.left: autolockSelector.left
                        anchors.topMargin: 4
                        anchors.leftMargin: autolockSelector.itemWidth * (0.5 + stateView.AutolockTypeTarget) + autolockSelector.spacing * stateView.AutolockTypeTarget

                        property bool show: (altMode || stateView.AutolockTypeFact != stateView.AutolockTypeTarget) && stateView.AutolockTypeTarget >= 0

                        Image {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            source: "Slices/autolock-cursor.png"
                            scale: parent.show ? 0.25 : 2
                            Behavior on scale { PropertyAnimation { duration: 100 } }
                            smooth: true
                        }
                        //opacity: stateView.AutolockTypeFact != stateView.AutolockTypeTarget ? 1 : 0

                        opacity: show ? 1 : 0
                        Behavior on opacity { PropertyAnimation { duration: 100 } }
                        Behavior on anchors.leftMargin { PropertyAnimation { duration: 170 } }
                    }
//                    Timer {
//                        interval: 1000
//                        running: true
//                        repeat: true
//                        onTriggered:
//                        {
//                            if (stateView.AutolockTypeFact != stateView.AutolockTypeTarget)
//                                stateView.AutolockTypeFact = (stateView.AutolockTypeFact + 1) % 3
//                        }
//                    }
                }

            }

            Rectangle {
                id: rightButton2Container
                height: 120
                color: "#00000000"
                anchors.right: parent.right
                anchors.left: parent.left

                // Содержимое кнопки смены режима движения
                // (Кнопка РМП)
                Rectangle {
                    id: page1buttonHeader
                    anchors.fill: parent
                    visible: !altMode
                    color: "#00000000"

                    // Фон области индикаторов режима
                    Image {
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        source: "Slices/drivemode-bck.png"
                    }

                    // Индикаторы режима движения
                    Column {
                        id: drivemodeSwitch
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.leftMargin: 4
                        spacing: 4

                        Repeater {
                            model: [ "П", "М", "Р", " ", "Т" ]
                            Row {
                                //height: 16
                                spacing: 12
                                Image {
                                    visible: modelData != " "
                                    source: "Slices/drivemode-led-" +
                                            (getDriveModeLetter(stateView.DriveModeTarget) == modelData ? "" : "un") + "selected" +
                                            (getDriveModeLetter(stateView.DriveModeFact) == modelData ? "-confirmed" : "") +
                                            ".png"
                                }
                                Text {
                                    visible: modelData != " "
                                    color: modelData != "Т" ? "#ccc" : "#ffffff00"
                                    text: modelData
                                }

                                // Заглушка - сепаратор
                                Rectangle {
                                    visible: modelData == " "
                                    height: 3
                                    width: 10
                                    color: "#00000000"
                                }
                            }
                        }
                    }

                    // Индикаторы режима
                    Column {
                        anchors.verticalCenter: drivemodeSwitch.verticalCenter
                        anchors.left: drivemodeSwitch.right
                        anchors.leftMargin: 3
                        spacing: 4

                        Repeater {
                            model: [ "iron", "rubber" ]
                            Row {
                                Image {
                                    source: "Slices/drivemode-wheels-mode-" +
                                            modelData +
                                            (stateView.IronWheels == (modelData == "iron") ? "-active" : "") +
                                            ".png"
                                }
                                Row {
                                    spacing: 3
                                    anchors.bottom: parent.bottom
                                    Image {
                                        anchors.verticalCenter: parent.verticalCenter
                                        source: "Slices/drivemode-wheels-indicator" +
                                                (stateView.IronWheels == (modelData == "iron") ? "-active" : "") +
                                                ".png"
                                        Image {
                                            source: "Slices/drivemode-wheels-icon-" +
                                                    modelData +
                                                    ".png"
                                            anchors.verticalCenter: parent.verticalCenter
                                            anchors.horizontalCenter: parent.horizontalCenter
                                        }
                                    }
                                    Text {
                                        anchors.verticalCenter: parent.verticalCenter
                                        color: "#ccc"
                                        text: {
                                            switch(modelData)
                                            {
                                                case "iron": return "Ж/Д"
                                                case "rubber": return "Дорожный"
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    // Подпись кнопки РМП
                    Column {
                        anchors.top: parent.top
                        anchors.topMargin: 15
                        anchors.right: parent.right
                        anchors.rightMargin: 22
                        spacing: -4
                        Text {
                            anchors.right: parent.right
                            color: "#ccc"
                            text: "Режим"
                            font.pixelSize: 20
                            font.bold: true
                        }
                        Text {
                            anchors.right: parent.right
                            color: "#ccc"
                            text: "движения"
                            font.pixelSize: 14
                        }
                    }
                }

                Column {
                    id: page1buttonAltHeader
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    visible: altMode

                    Text {
                        color: "#ffffff"
                        text: qsTr("Отмена\nКрасного")
                        font.pointSize: 16
                        font.family: "URW Gothic L"
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    onPressed: switchPage(1)
                }
            }
            Rectangle {
                id: rightButton3Container
                    height: 120
                    color: "#00000000"
                    anchors.right: parent.right
                    anchors.left: parent.left

                    // Переключатель страниц
                    Rectangle {
                        id: page2buttonHeader
                        anchors.fill: parent
                        anchors.rightMargin: leftBorder.width
                        visible: !altMode
                        clip: true
                        color: "#00000000"

                        Image {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.right
                            source: "Slices/Panel-Left-PageSwitcher-FlipFlop.png"
                            smooth: true

                            rotation: { switch (pageNum)
                                          {
                                            case 0: return 0
                                            case 1: return -90
                                          }}
                            Behavior on rotation { SmoothedAnimation { duration: 1000 } }
                        }

                        Text {
                            anchors.right: parent.right
                            anchors.rightMargin: 15
                            anchors.top: parent.top
                            anchors.topMargin: 10
                            color: "#ffffff"
                            text: qsTr("Карта")
                            font.pointSize: 16
                            font.family: "URW Gothic L"
                        }
                        Text {
                            anchors.right: parent.right
                            anchors.rightMargin: 15
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 10
                            color: "#ffffff"
                            text: qsTr("Датчики")
                            font.pointSize: 16
                            font.family: "URW Gothic L"
                        }

                    }

                    Column {
                        id: page2buttonAltHeader
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.verticalCenter: parent.verticalCenter
                        visible: altMode

                        Text {
                            color: "#ffffff"
                            text: qsTr("Ввод\nпараметров")
                            font.pointSize: 16
                            font.family: "URW Gothic L"
                        }
                    }
                    MouseArea {
                        anchors.fill: parent
                        onPressed: switchPage(2)
                    }
            }

            Rectangle {
                id: rightButton4Container
                height: 120
                color: "#00000000"
                anchors.right: parent.right
                anchors.left: parent.left

                Rectangle {
                    anchors.fill: parent
                    color: "#30000000"
                    anchors.rightMargin: 7
                    anchors.topMargin: 4
                    visible: altMode
                }

                Column {
                    id: page4buttonAltHeader
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    anchors.verticalCenter: parent.verticalCenter

                    Text {
                        color: "#ffffff"
                        text: qsTr("Alt")
                        font.pointSize: 20
                        font.family: "URW Gothic L"
                    }
                }
            }

        }


    }

    Rectangle {
        id: panelRight

        x: 652
        y: 0
        width: 149
        height: 480
        color: "#00000000"
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.top: parent.top

        Image {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            source: "Slices/Panel-Right.png"
        }



        Image {
            id: vigilanceSign
            anchors.topMargin: 15
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter

            source: "Slices/Vigilance-Sign-Inactive.png"

            Image {
                anchors.fill: parent
                source: "Slices/Vigilance-Sign-Active-Overlay.png"
                property bool isActive: false;
                opacity: 1.0 * isActive
                Behavior on opacity { PropertyAnimation { duration: 70 } }

                Timer {
                    interval: 400
                    running: stateView.IsVigilanceRequired || (parent.isActive)
                    repeat: true
                    onTriggered: parent.isActive = !parent.isActive
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: stateView.IsVigilanceRequired = !stateView.IsVigilanceRequired;
            }
        }


        Rectangle {
            id: graduateBar

            width: 10

            color: "#00000000"
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.bottomMargin: speedBox.height
            anchors.left: parent.left

            Repeater {
                id: repeater
                model: Math.floor(maxSpeed/5) - 1

                Rectangle {
                    property int sp: (index + 1) * 5
                    property bool nice: sp % 10 == 0

                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    y: graduateBar.height - (graduateBar.height / maxSpeed) * sp - height/2
                    visible: y > vigilanceSign.y + vigilanceSign.height

                    width: 20
                    height: 14;
                    color: "#00000000"

                    Repeater {
                        model: [ "#71000000", "#a8ffffff" ]
                        Row
                        {
                            anchors.verticalCenterOffset: index-1
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: index
                            spacing: 3

                            Rectangle {
                                anchors.verticalCenter: parent.verticalCenter;
                                height: nice? 2:1;
                                color: modelData;
                                width: 6; // + 0.4*Math.floor(repeater.count / 6) * index;
                            }
                            Text {
                                anchors.verticalCenter: parent.verticalCenter;
                                text: parent.parent.sp;
                                font.family: "URW Gothic L";
                                font.pointSize: 8;
                                color: modelData
                            }
                        }
                    }
                }
            }
        }


        Rectangle {
            x: 0
            y: 0
            width: 7
            height: rootRect.height - speedBox.height
            color: "#fff"
            anchors.top: parent.top
            opacity: graduateBar.opacity
        }

        Rectangle {
            id: speedValueBar
            x: 0
            width: 7
            height: (stateView.Speed/maxSpeed)*(rootRect.height - speedBox.height)
            visible: stateView.Speed >= 0
            color: "#4999c9"
            anchors.bottom: speedBox.top
            opacity: graduateBar.opacity

            Behavior on height { SmoothedAnimation { duration: 500 } }
        }

        Rectangle {
            id: restrictionBar
            x: 0
            y: 0
            width: 7
            height: (rootRect.height - speedBox.height) - (stateView.SpeedRestriction/maxSpeed)*(rootRect.height - speedBox.height)
            color: "#c94949"
            anchors.top: parent.top
            opacity: graduateBar.opacity

            Behavior on height { SmoothedAnimation { duration: 500 } }
        }

        Rectangle {
            width: 63
            height: 64
            color: "#00000000"
            id: speedBox
            anchors.right: parent.left
            anchors.bottom: parent.bottom

            Image {
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                source: "Slices/Speedbox-Label.png"
            }

            Repeater {
                model: [ "#ff30759e", "#d8ffffff" ]
                Column {
                    y: index
                    anchors.right: parent.right
                    anchors.rightMargin: 10-index

                    Text {
                        text: stateView.SpeedIsValid ? stateView.Speed.toFixed() : "--"
                        anchors.right: parent.right
                        height: 38
                        color: modelData
                        font.pointSize: 26
                        font.family: "URW Gothic L"
                        font.bold: true
                    }
                    Text {
                        text: qsTr("км/ч")
                        anchors.right: parent.right
                        color: modelData
                        font.pointSize: 11.2
                        font.family: "URW Gothic L"
                        font.bold: true
                    }
                }
            }
        }


        // Светофор
        Image {
            id: name
            source: "Slices/Panel-Right-Lightbox-Bck.png"
            anchors.right: parent.right
            anchors.rightMargin: getDriveModeLetter(stateView.DriveModeFact) != "Т" ? -3 : -width
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 55
            Behavior on anchors.rightMargin { SmoothedAnimation { duration: 1000 } }

            ListView {
                id: lightsPanel
                width: 54
                height: 280
                interactive: false
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 8

                currentIndex: 2

                delegate: Item {
                    height: 55
                    width: 54

                    Rectangle {
                        anchors.fill: parent
                        color: "#00000000"

                        Image {
                            id: lightOffImage
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                            source: "Slices/Light-Off.png"
                        }
                        Image {
                            id: lightOnImage
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                            source: "Slices/Light-" + name + ".png"
                            opacity: 0
                        }

                        state: stateView.Light == permissiveIndex ? "On" : "Off"

                        states: [
                            State {
                                name: "On"
                                PropertyChanges { target: lightOnImage; opacity: 1 }
                                PropertyChanges { target: lightOffImage; opacity: 0 }
                            },
                            State {
                                name: "Off"
                            }
                        ]

                        transitions: Transition {
                            NumberAnimation { targets: [lightOnImage, lightOffImage]; properties: "opacity"; easing.type: Easing.InQuad; duration: 300 }
                        }
                    }
                }
                model: ListModel {
                    ListElement {
                        name: "Green"
                        permissiveIndex: 3
                    }
                    ListElement {
                        name: "Yellow"
                        permissiveIndex: 2
                    }
                    ListElement {
                        name: "YellowRed"
                        permissiveIndex: 1
                    }
                    ListElement {
                        name: "Red"
                        permissiveIndex: 0
                    }
                    ListElement {
                        name: "White"
                        permissiveIndex: -1
                    }
                }
            }
        }
    }


    Rectangle {
        anchors.fill: rootRect
        color: "#00000000"
        Image {
            source: "Slices/InputMode-Background.png"
            opacity: inputMode ? 1 : 0
            Behavior on opacity { SmoothedAnimation { duration: 2000 } }
        }
    }

    Column {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: inputMode ? 0 : -width
        Behavior on anchors.leftMargin { SmoothedAnimation { duration: 300 } }
        Repeater {
            model: ["Изм.", ">", "<", "OK"]
            Rectangle {
                height: (rootRect.height) / 4
                width: 77
                anchors.left: parent.left
                color: "#00000000"
                Image{
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    source: "Slices/InputMode-Button.png"
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 16
                        text: modelData
                        font.pixelSize: 24
                        font.family: "URW Gothic L"
                        font.bold: true
                        color: "#ffe0e0e0"
                    }
                }
            }
        }
    }

    Rectangle {
        id: inputModeParentField
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#00000000"
        width: 420
        height: 75
        visible: inputMode

        Image{
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            source: "Slices/InputMode-Field.png"
        }

        Column{
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 24
            spacing: 26

            Row{
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 50
                Rectangle{
                    id: inputModeRail
                    property int startPosition: 0
                    property int positionsCount: 3
                    width: 20*positionsCount
                    height: 54
                    color: "#00000000"

                    Text{
                        anchors.top: parent.top
                        anchors.topMargin: 30
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.family: "URW Gothic L"
                        font.pixelSize: 18
                        font.bold: true
                        color: "#ffe0e0e0"
                        text: qsTr("Путь")
                    }

                    Row {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: parent.top
                        height: 30
                        spacing: 0
                        Repeater {
                            model: parent.parent.positionsCount
                            Image {
                                property int myCursorIndex: parent.parent.startPosition+index
                                anchors.verticalCenter: parent.verticalCenter
                                source: "Slices/InputMode-InputPosition.png"
                                Text {
                                    text: inputPositions[parent.myCursorIndex]
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.pixelSize: 24
                                    font.family: "URW Gothic L"
                                    font.bold: true
                                    color: "#ff474747"
                                }
                                Image {
                                    anchors.bottom: parent.bottom
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    source: "Slices/InputMode-Cursor.png"
                                    property bool isActive: false;
                                    opacity:  1.0 * (inputCursorIndex == parent.myCursorIndex) * isActive
                                    Behavior on opacity { PropertyAnimation { duration: 70 } }

                                    Timer {
                                        interval: 400
                                        running: inputCursorIndex == parent.parent.myCursorIndex
                                        repeat: true
                                        onTriggered: parent.isActive = !parent.isActive
                                        onRunningChanged: parent.isActive = true
                                    }
                                }
                            }
                        }
                    }
                }

                Rectangle{
                    id: inputModeMachinist
                    property int startPosition: 3
                    property int positionsCount: 4
                    width: 20*positionsCount
                    height: 54
                    color: "#00000000"

                    Text{
                        anchors.top: parent.top
                        anchors.topMargin: 30
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.family: "URW Gothic L"
                        font.pixelSize: 18
                        font.bold: true
                        color: "#ffe0e0e0"
                        text: qsTr("Машинист")
                    }

                    Row {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: parent.top
                        height: 30
                        spacing: 0
                        Repeater {
                            model: parent.parent.positionsCount
                            Image {
                                property int myCursorIndex: parent.parent.startPosition+index
                                anchors.verticalCenter: parent.verticalCenter
                                source: "Slices/InputMode-InputPosition.png"
                                Text {
                                    text: inputPositions[parent.myCursorIndex]
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.pixelSize: 24
                                    font.family: "URW Gothic L"
                                    font.bold: true
                                    color: "#ff474747"
                                }
                                Image {
                                    anchors.bottom: parent.bottom
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    source: "Slices/InputMode-Cursor.png"
                                    property bool isActive: false;
                                    opacity:  1.0 * (inputCursorIndex == parent.myCursorIndex) * isActive
                                    Behavior on opacity { PropertyAnimation { duration: 70 } }

                                    Timer {
                                        interval: 400
                                        running: inputCursorIndex == parent.parent.myCursorIndex
                                        repeat: true
                                        onTriggered: parent.isActive = !parent.isActive
                                        onRunningChanged: parent.isActive = true
                                    }
                                }
                            }
                        }
                    }
                }

                Rectangle{
                    id: inputModeTrain
                    property int startPosition: 7
                    property int positionsCount: 4
                    width: 20*positionsCount
                    height: 54
                    color: "#00000000"

                    Text{
                        anchors.top: parent.top
                        anchors.topMargin: 30
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.family: "URW Gothic L"
                        font.pixelSize: 18
                        font.bold: true
                        color: "#ffe0e0e0"
                        text: qsTr("Поезд")
                    }

                    Row {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: parent.top
                        height: 30
                        spacing: 0
                        Repeater {
                            model: parent.parent.positionsCount
                            Image {
                                property int myCursorIndex: parent.parent.startPosition+index
                                anchors.verticalCenter: parent.verticalCenter
                                source: "Slices/InputMode-InputPosition.png"
                                Text {
                                    text: inputPositions[parent.myCursorIndex]
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.pixelSize: 24
                                    font.family: "URW Gothic L"
                                    font.bold: true
                                    color: "#ff474747"
                                }
                                Image {
                                    anchors.bottom: parent.bottom
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    source: "Slices/InputMode-Cursor.png"
                                    property bool isActive: false;
                                    opacity:  1.0 * (inputCursorIndex == parent.myCursorIndex) * isActive
                                    Behavior on opacity { PropertyAnimation { duration: 70 } }

                                    Timer {
                                        interval: 400
                                        running: inputCursorIndex == parent.parent.myCursorIndex
                                        repeat: true
                                        onTriggered: parent.isActive = !parent.isActive
                                        onRunningChanged: parent.isActive = true
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Row{
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 60

                Rectangle{
                    id: inputModeLengthWagon
                    property int startPosition: 11
                    property int positionsCount: 3
                    width: 20*positionsCount
                    height: 64
                    color: "#00000000"

                    Text{
                        anchors.top: parent.top
                        anchors.topMargin: 30
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.family: "URW Gothic L"
                        font.pixelSize:16
                        font.bold: true
                        color: "#ffe0e0e0"
                        text: qsTr("Вагонов")
                    }

                    Row {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: parent.top
                        height: 26
                        spacing: 0
                        Repeater {
                            model: parent.parent.positionsCount
                            Image {
                                property int myCursorIndex: parent.parent.startPosition+index
                                anchors.verticalCenter: parent.verticalCenter
                                source: "Slices/InputMode-InputPosition.png"
                                height: 26
                                width: 17
                                Text {
                                    text: inputPositions[parent.myCursorIndex]
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.pixelSize: 21
                                    font.family: "URW Gothic L"
                                    font.bold: true
                                    color: "#ff474747"
                                }
                                Image {
                                    anchors.bottom: parent.bottom
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    source: "Slices/InputMode-CursorSmall.png"
                                    property bool isActive: false;
                                    opacity:  1.0 * (inputCursorIndex == parent.myCursorIndex) * isActive
                                    Behavior on opacity { PropertyAnimation { duration: 70 } }

                                    Timer {
                                        interval: 400
                                        running: inputCursorIndex == parent.parent.myCursorIndex
                                        repeat: true
                                        onTriggered: parent.isActive = !parent.isActive
                                        onRunningChanged: parent.isActive = true
                                    }
                                }
                            }
                        }
                    }
                }

                Rectangle{
                    id: inputModeLengthAxle
                    property int startPosition: 14
                    property int positionsCount: 3
                    width: 20*positionsCount
                    height: 64
                    color: "#00000000"

                    Text{
                        anchors.top: parent.top
                        anchors.topMargin: 30
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.family: "URW Gothic L"
                        font.pixelSize:16
                        font.bold: true
                        color: "#ffe0e0e0"
                        text: qsTr("Осей")
                    }

                    Row {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: parent.top
                        height: 26
                        spacing: 0
                        Repeater {
                            model: parent.parent.positionsCount
                            Image {
                                property int myCursorIndex: parent.parent.startPosition+index
                                anchors.verticalCenter: parent.verticalCenter
                                source: "Slices/InputMode-InputPosition.png"
                                height: 26
                                width: 17
                                Text {
                                    text: inputPositions[parent.myCursorIndex]
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.pixelSize: 21
                                    font.family: "URW Gothic L"
                                    font.bold: true
                                    color: "#ff474747"
                                }
                                Image {
                                    anchors.bottom: parent.bottom
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    source: "Slices/InputMode-CursorSmall.png"
                                    property bool isActive: false;
                                    opacity:  1.0 * (inputCursorIndex == parent.myCursorIndex) * isActive
                                    Behavior on opacity { PropertyAnimation { duration: 70 } }

                                    Timer {
                                        interval: 400
                                        running: inputCursorIndex == parent.parent.myCursorIndex
                                        repeat: true
                                        onTriggered: parent.isActive = !parent.isActive
                                        onRunningChanged: parent.isActive = true
                                    }
                                }
                            }
                        }
                    }
                }

                Rectangle{
                    id: inputModeMass
                    property int startPosition: 17
                    property int positionsCount: 4
                    width: 20*positionsCount
                    height: 64
                    color: "#00000000"

                    Text{
                        anchors.top: parent.top
                        anchors.topMargin: 30
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.family: "URW Gothic L"
                        font.pixelSize: 16
                        font.bold: true
                        color: "#ffe0e0e0"
                        text: qsTr("Масса")
                    }

                    Row {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: parent.top
                        height: 26
                        spacing: 0
                        Repeater {
                            model: parent.parent.positionsCount
                            Image {
                                 property int myCursorIndex: parent.parent.startPosition+index
                                anchors.verticalCenter: parent.verticalCenter
                                source: "Slices/InputMode-InputPosition.png"
                                height: 26
                                width: 17
                                Text {
                                    text: inputPositions[parent.myCursorIndex]
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.pixelSize: 21
                                    font.family: "URW Gothic L"
                                    font.bold: true
                                    color: "#ff474747"
                                }
                                Image {
                                    anchors.bottom: parent.bottom
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    source: "Slices/InputMode-CursorSmall.png"
                                    property bool isActive: false;
                                    opacity:  1.0 * (inputCursorIndex == parent.myCursorIndex) * isActive
                                    Behavior on opacity { PropertyAnimation { duration: 70 } }

                                    Timer {
                                        interval: 400
                                        running: inputCursorIndex == parent.parent.myCursorIndex
                                        repeat: true
                                        onTriggered: parent.isActive = !parent.isActive
                                        onRunningChanged: parent.isActive = true
                                    }
                                }
                            }
                        }
                    }
                }
            }

        }


    }

}
