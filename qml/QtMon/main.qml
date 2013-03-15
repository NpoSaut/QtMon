import QtQuick 1.1
import views 1.0

Rectangle {
    width: 800
    height: 480
    id: rootRect

    state: "page1"

    property int pageNum: 1

    property double maxSpeed: 100

    function switchPage(i) {
        if (i == 1) {
            rootRect.state = "page1";
        }
        if (i == 2) {
            rootRect.state = "page2";
        }
    }

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


    focus: true
    Keys.onPressed: {
        if (event.key == Qt.Key_F1) {
            // Send CAN requset to change ALSN freq

            // Emulation
            if ( stateView.AlsnFreq == 25 )
                stateView.AlsnFreq = 50;
            else if ( stateView.AlsnFreq == 50 )
                stateView.AlsnFreq = 75;
            else if ( stateView.AlsnFreq == 75 )
                stateView.AlsnFreq = 25;
            else
                stateView.AlsnFreq = 25;
        }
        else if (event.key == Qt.Key_F2) {
            stateView.PropertyView = false;
        }
        else if (event.key == Qt.Key_F3) {
            stateView.PropertyView = true;
        }
        else if (event.key == Qt.Key_F4) {
            // Reserved
        }
    }


    SystemStateView {
        id: stateView
        objectName: "stateView"
    }


    states: [
        State {
            name: "page1"
            when: (stateView.PropertyView == false)
            PropertyChanges { target: page1indicator; width: 12 }
            PropertyChanges { target: page2indicator; width: 6 }
            PropertyChanges { target: pagesContainer; y: 0 }

            PropertyChanges { target: page2buttonHeader; anchors.rightMargin: 22 }
            PropertyChanges { target: page1buttonInfo; anchors.rightMargin: 20; opacity: 0.05 }
        },
        State {
            name: "page2"
            when: (stateView.PropertyView == true)
            PropertyChanges { target: page1indicator; width: 6 }
            PropertyChanges { target: page2indicator; width: 12 }
            PropertyChanges { target: pagesContainer; y: -1 * pagesArea.height }

            PropertyChanges { target: page1buttonHeader; anchors.rightMargin: 22 }
            //PropertyChanges { target: page2buttonInfo; anchors.rightMargin: -20; opacity: 0.00 }
        }
    ]

    transitions: Transition {
        NumberAnimation { target: pagesContainer; properties: "y"; easing.type: Easing.InOutQuad; duration: 500 }
        NumberAnimation { targets: [page1indicator, page2indicator]; properties: "width"; easing.type: Easing.InOutQuad; duration: 200 }
        NumberAnimation { targets: [page1buttonHeader, page2buttonHeader]; properties: "anchors.rightMargin"; easing.type: Easing.InOutQuad; duration: 400 }
        NumberAnimation { target: page1buttonInfo; properties: "opacity"; easing.type: Easing.InOutQuad; duration: 400 }
        NumberAnimation { target: page1buttonInfo; properties: "anchors.rightMargin"; easing.type: Easing.OutQuad; duration: 800 }
    }

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
                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "#6b6b6b"
                    }

                    GradientStop {
                        position: 1
                        color: "#2b2b2b"
                    }
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

                           text: qsTr("КООРДИНАТА")
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
                               text: qsTr("123км 400пк 00м")
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
                               text: qsTr("1ПР")
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
                              text: stateView.Acceleration
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
                   Rectangle {
                       color: "#20000000"
                       border.color: "#ffffff00"
                       width: 20
                       height: 20
                       Text {
                           anchors.horizontalCenter: parent.horizontalCenter
                           anchors.verticalCenter: parent.verticalCenter
                           text: stateView.DriveMode
                           //text: qsTr("П")
                           //text: stateView.Time


                           color: "#ffffffff"
                           font.pixelSize: 14
                           font.family: "URW Gothic L"
                       }
                   }

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
                property int tickCount: 10

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
                    source: "Slices/Needle-Speed.png"

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
                    //property double angle: speedometer.minAngle - (stateView.SpeedRestriction - 20) * speedometer.anglePerKph
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

                    // Текущая скорость
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter

                        text: stateView.Speed
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

                        text: stateView.SpeedRestriction
                        color: "#c94949"

                        font.pixelSize: 35
                        font.family: "URW Gothic L"
                        font.bold: true
                    }

                }
            }

            // Треугольники направления движения
            Row {
                spacing: 90
                anchors.horizontalCenter: speedometer.horizontalCenter
                anchors.bottom: speedometer.bottom
                anchors.bottomMargin: 10

                Image {
                    opacity: stateView.Direction==1 ? 1 : 0.05
                    source: "Slices/Direction-Forward.png"
                }
                Image {
                    opacity: stateView.Direction==-1 ? 1 : 0.05
                    source: "Slices/Direction-Back.png"
                }
            }

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

                            source: "MapTiles/" + horizontalIndex + "-" + verticalIndex + ".png"
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
                    x: 534
                    y: 364
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "Slices/Cross.png"
                }

                Rectangle {
                    id: hintBox

                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: -10
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: background.height
                    width: background.width

                    color: "#00000000"

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
                        text: stateView.Date;
                       //text: qsTr("21 декабря 2012");

                        anchors.top: parent.top
                        anchors.topMargin: 3
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.horizontalCenterOffset: 5

                        font.family: "URW Gothic L"; font.pixelSize: 14;
                        color: "#2d2d2d";
                    }

                    Text {
                        id: hintBoxMilageKm
                        text: Math.round(stateView.Milage/1000) + qsTr('.')
                                + Math.round(stateView.Milage/100)%10 + qsTr(" км")

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

        // Очень плохо, что это здесь находится!!!
        Image {
            id: alsnSwitchBackgroundCircle
            anchors.right: parent.left
            anchors.rightMargin: -60
            anchors.top: parent.top
            anchors.topMargin: -height/2 + 60

            fillMode: "Tile"
            source: "Slices/alsn-switch.png"
        }

        Image {
            x: -14
            y: 104
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            source: "Slices/Panel-Left-Middle.png"
        }

        Rectangle {
            width: 6
            color: "#4999c9"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.top: parent.top
        }

        Column {
            x: -6
            y: 0
            anchors.fill: parent

            Rectangle {
                id: rightButton1Container
                height: 120
                color: "#00000000"
                anchors.right: parent.right
                anchors.left: parent.left

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
                    property string objColor: "#ffdddddd"

                    Repeater
                    {
                        model: [25, 50, 75]

                        Rectangle {
                            property real myRot: (1 - index) * alsnSwitch.angle
                            property int freq: modelData

                            x: alsnSwitch.width/2 + alsnSwitch.radius * Math.cos(myRot / 180 * Math.PI)
                            y: alsnSwitch.height/2 + alsnSwitch.radius * Math.sin(myRot / 180 * Math.PI)
                            rotation: myRot

                            color: alsnSwitch.objColor
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
                            when: (stateView.AlsnFreq != 25 && tateView.AlsnFreq != 50 && tateView.AlsnFreq != 75)
                            PropertyChanges { target: alsnSwitch; rotation: -2 * alsnSwitch.angle }
                        },
                        State {
                            name: "alsn25"
                            when: (stateView.AlsnFreq == 25)
                            PropertyChanges { target: alsnSwitch; rotation: -1 * alsnSwitch.angle }
                        },
                        State {
                            name: "alsn50"
                            when: (stateView.AlsnFreq == 50)
                            PropertyChanges { target: alsnSwitch; rotation: 0 * alsnSwitch.angle }
                        },
                        State {
                            name: "alsn75"
                            when: (stateView.AlsnFreq == 75)
                            PropertyChanges { target: alsnSwitch; rotation: +1 * alsnSwitch.angle }
                        }
                    ]

                    transitions: Transition {
                        NumberAnimation { target: alsnSwitch; properties: "rotation"; easing.type: Easing.InOutQuad; duration: 200 }
                    }
                }
            }

            Rectangle {
                id: rightButton2Container
                height: 120
                color: "#00000000"
                anchors.right: parent.right
                anchors.left: parent.left

                Rectangle {
                    id: page1indicator
                    width: 6
                    color: "#4999c9"
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 1
                    anchors.top: parent.top
                    anchors.topMargin: -1
                }

                Column {
                    id: page1buttonHeader
                    x: 25
                    y: 32
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    //anchors.left: parent.left
                    //anchors.leftMargin: 25
                    anchors.verticalCenter: parent.verticalCenter

                    Text {
                        color: "#ffffff"
                        text: qsTr("Ж/Д")
                        font.pointSize: 20
                        font.family: "URW Gothic L"
                    }

                    Row {
                        id: page1buttonInfo
                        spacing: 2
                        anchors.right: parent.right
                        Text {
                            color: "#4999c9"
                            text: stateView.Speed
                            anchors.bottom: parent.bottom
//                            font.bold: true
                            font.pointSize: 17
                            font.family: "URW Gothic L"
                        }
                        Text {
                            color: "#ffffff"
                            text: qsTr("/")
                            anchors.bottom: parent.bottom
//                            font.bold: true
                            font.pointSize: 14
                            font.family: "URW Gothic L"
                        }
                        Text {
                            color: "#c94949"
                            text: stateView.SpeedRestriction
                            anchors.bottom: parent.bottom
//                            font.bold: true
                            font.pointSize: 14
                            font.family: "URW Gothic L"
                        }
                        }
                }
                MouseArea {
                    anchors.fill: parent
                    onPressed: switchPage(1)
                }
            }
            Rectangle {
                id: rightButton3Container
                    x: 0
                    y: 120
                    height: 120
                    color: "#00000000"
                    anchors.right: parent.right
                    anchors.left: parent.left

                    Rectangle {
                        id: page2indicator
                        width: 6
                        color: "#4999c9"
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: -3
                        anchors.top: parent.top
                        anchors.topMargin: 1
                    }
                    Column {
                        id: page2buttonHeader
                        anchors.right: parent.right
                        anchors.rightMargin: 14
                        //anchors.left: parent.left
                        //anchors.leftMargin: 25
                        anchors.verticalCenter: parent.verticalCenter

                        Text {
                            color: "#ffffff"
                            text: qsTr("Дорожный")
                            font.pointSize: 18
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
                opacity: 0
                Behavior on opacity { PropertyAnimation { duration: 70; easing: Easing.InOutCubic } }

                Timer {
                    interval: 400
                    running: stateView.IsVigilanceRequired || (parent.opacity != 0)
                    repeat: true
                    onTriggered: parent.opacity = 1 - parent.opacity
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: stateView.IsVigilanceRequired = !stateView.IsVigilanceRequired;
            }
        }


        ListView {
            id: lightsPanel
            x: 7
            y: 123
            width: 54
            height: 280
            anchors.horizontalCenterOffset: 15
            interactive: false
            anchors.horizontalCenter: parent.horizontalCenter

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
