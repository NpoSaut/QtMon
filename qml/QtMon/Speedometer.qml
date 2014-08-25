import QtQuick 1.1

Rectangle {
    property double speed: 40
    property double speedRestriction: 80
    property double maxSpeed: 180

    property alias speedWarningLimit: speedometerWarner.warningLimit
    signal speedWarningPoolsed

    color: "#00000000"

    // Спидометр
    Rectangle {
        id: speedometer
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        color: "#00000000"
        width: Math.min(parent.width, parent.height)
        height: width

        // Количество засечек
        property double speedStep: 5 * (Math.pow(2, Math.floor(Math.log(maxSpeed / 45) / Math.log(2))))
        property int tickCount: maxSpeed / speedStep

        property double minAngle: 1.25 * Math.PI
        property double maxAngle: -0.25 * Math.PI
        property double anglePerKph: (minAngle - maxAngle) / maxSpeed

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

            height: (1 - Math.sin(
                         parent.minAngle)) * parent.tableRadius + filedWidth - 1

            color: "#00000000"
            clip: true

            // Дуга шкалы спидометра
            Rectangle {
                id: speedometerCircle
                color: "#00000000"
                border.color: "#fff"
                border.width: 3

                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right

                property double unFiledWidth: parent.filedWidth + border.width / 2
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
                property double tickDisstance: 28
                property double kph: index * (maxSpeed / speedometer.tickCount)
                property double angle: speedometer.minAngle - kph * speedometer.anglePerKph

                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenterOffset: -parent.tableRadius * Math.sin(
                                                  angle)
                anchors.horizontalCenterOffset: parent.tableRadius * Math.cos(
                                                    angle)

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
                    anchors.verticalCenterOffset: tickDisstance * Math.sin(parent.angle)
                    anchors.horizontalCenterOffset: -tickDisstance * Math.cos(parent.angle)
                    text: parent.kph
                    color: "#ffffffff"

                    font.pixelSize: 16 * 1.25
                    font.family: "URW Gothic L"
                }
            }
        }

        // Индикатор борзости (привышения допустимой скорости) вокруг кругляша скорости
        Timer {
            id: speedometerWarner
            property int warningLimit: 0
            property double warningLevel: Math.max(0, Math.min(warningLimit, speed + warningLimit - speedRestriction)) / warningLimit
            property bool warned: warningLevel > 0 && getDriveModeLetter(stateView.DriveModeFact) != "Т"
            property bool poolsed: warned && innerPoolsed
            property bool innerPoolsed: false
            property double nextInterval: 600 * (parent.poolsed ? 0.3 : 1.0) * (1.5 - warningLevel)
            interval: 100
            repeat: true
            running: speedometerWarner.warned
            onTriggered: {
                interval = nextInterval
                innerPoolsed = !innerPoolsed
                if (poolsed) {
                    speedWarningPoolsed()
                    speedRestrictionNeedlePulsingAnimation.start()
                }
            }
        }

        // Стрелка спидометра
        Image {
            source: stateView.SpeedIsValid ? ("Slices/Needle-Speed"
                                              + (speedometerWarner.poolsed ? "-Inversed" : "")
                                              + ".png") : "Slices/Needle-Speed-Invalid.png"

            rotation: 180 - Math.min(
                          speedometer.minAngle, Math.max(
                              speedometer.maxAngle - 0.1,
                              speedometer.minAngle - speedometer.anglePerKph
                              * speed)) * 180 / Math.PI
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
            property double angle: speedometer.minAngle - stateView.TargetSpeed
                                   * speedometer.anglePerKph

            anchors.verticalCenterOffset: -r * Math.sin(angle)
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
            id: speedRestrictionNeedle
            transformOrigin: Item.Right

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            property double r: parent.tableRadius + 4
            property double angle: speedometer.minAngle - stateView.SpeedRestriction
                                   * speedometer.anglePerKph

            anchors.verticalCenterOffset: -r * Math.sin(angle)
            anchors.horizontalCenterOffset: r * Math.cos(angle)

            rotation: 180 - angle * 180 / Math.PI

            SequentialAnimation {
                id: speedRestrictionNeedlePulsingAnimation
                //                        property bool playing: false
                //                        running: playing || speedometerWarner.poolsed
                NumberAnimation {
                    target: speedRestrictionNeedle
                    property: "scale"
                    to: 1.5
                    duration: 70
                    easing: Easing.OutCubic
                }
                NumberAnimation {
                    target: speedRestrictionNeedle
                    property: "scale"
                    to: 1
                    duration: 150
                    easing: Easing.InCubic
                }
                //                        onStarted: playing = true
                //                        onCompleted: playing = false
            }

            Image {
                source: "Slices/Needle-Restriction.png"
                smooth: true

                anchors.right: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        // Числа скорости и ограничения в кругляше в центре
        Rectangle {
            id: speedometerInnerCircle
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            width: 80 * 1.25
            height: width
            radius: width / 2

            color: speedometerWarner.poolsed ? "#fff" : "#4999c9"

            // Индикатор отсутствия тяги вокруг кругляша скорости
            Rectangle {
                property int thick: 3
                z: parent.z - 5
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                color: "#fff"
                width: parent.width + thick * 2
                height: width
                radius: width / 2
                visible: !stateView.IsTractionOn
            }

            // Текущая скорость
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter

                text: stateView.SpeedIsValid ? stateView.Speed.toFixed() : "N/A"
                color: speedometerWarner.poolsed ? "#4999c9" : "#fff"

                font.pixelSize: 35 * 1.25
                font.family: "URW Gothic L"
                font.bold: true
            }

            // Ограничение скорости
            Rectangle {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 65 * 1.25
                width: 60
                height: 40
                radius: 4
                color: speedometerWarner.warned ? "#a0ffffff" : "#00000000"
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter

                    text: stateView.SpeedRestriction.toFixed()
                    color: speedometerWarner.warned ? "#ee1616" : "#c94949"

                    font.pixelSize: 35 * 1.25
                    font.family: "URW Gothic L"
                    font.bold: true
                }
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
            source: stateView.Direction
                    == 1 ? "Slices/Direction-Forward.png" : "Slices/Direction-None.png"
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
            source: stateView.Direction
                    == -1 ? "Slices/Direction-Back.png" : "Slices/Direction-None.png"
        }
    }
}
