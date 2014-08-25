import QtQuick 1.1
import views 1.0

Rectangle {
    width: 800
    height: 600
    id: rootRect

    property color accentColor: "#eacc2e"
    property color regularColor: "#fff"

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
            width: 250
            //color: "#20ff00ff"
            color: "#00000000"

            Column {
                anchors.left: parent.left
                anchors.right: parent.right
                spacing: 4

                Column {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: accentColor
                        font.pixelSize: 14
                        font.family: "URW Gothic L"
                        text: "КООРДИНАТА"
                    }
                    ParameterBox {
                        height: 20
                        anchors.left: parent.left
                        anchors.right: parent.right
                        borderColor: accentColor
                        textColor: rootRect.regularColor
                        text: "128км 7пк 23м"
                    }
                }

                HorizontalLabeledParameterBox {
                    labelText: "Путь:"
                    text: "7"
                    labelWidth: parent.width * 2.0 / 3.0
                    accentColor: rootRect.accentColor
                    regularColor: rootRect.regularColor
                    anchors.left: parent.left
                    anchors.right: parent.right
                }

                Row {
                    id: frequncyIndicator
                    anchors.left: parent.left
                    anchors.right: parent.right
                    Repeater {
                        model: [ 25, 50, 75 ]
                        Indicator {
                            text: modelData
                            isActive: modelData == 50
                            width: frequncyIndicator.width / 3.0
                            accentColor: rootRect.accentColor
                            textColor: "#30ffffff"
                        }
                    }
                }
            }
        }

        // Спидометр с треуольниками движения
        Speedometer {
            width: 300
            height: 300
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter

            speed: stateView.Speed;
            speedRestriction: stateView.SpeedRestriction;
            maxSpeed: 20 * Math.ceil(stateView.DesignSpeed * 1.35 / 20);

            speedWarningLimit: 3
            onSpeedWarningPoolsed: stateView.SpeedWarningFlash()
        }
    }
}
