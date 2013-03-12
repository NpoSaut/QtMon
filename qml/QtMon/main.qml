import QtQuick 1.1
import views 1.0

Rectangle {
    width: 800
    height: 480
    id: rootRect

    state: "page1"

    property int pageNum: 1

    property double maxSpeed: 160

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

            PropertyChanges { target: page1buttonHeader; anchors.leftMargin: 22 }
            PropertyChanges { target: page1buttonInfo; anchors.rightMargin: -20; opacity: 0.0 }
        },
        State {
            name: "page2"
            when: (stateView.PropertyView == true)
            PropertyChanges { target: page1indicator; width: 6 }
            PropertyChanges { target: page2indicator; width: 12 }
            PropertyChanges { target: pagesContainer; y: -1 * pagesArea.height }

            PropertyChanges { target: page2buttonHeader; anchors.leftMargin: 22 }
            PropertyChanges { target: page2buttonInfo; anchors.rightMargin: -20; opacity: 0.00 }
        }
    ]

    transitions: Transition {
        NumberAnimation { target: pagesContainer; properties: "y"; easing.type: Easing.InOutQuad; duration: 500 }
        NumberAnimation { targets: [page1indicator, page2indicator]; properties: "width"; easing.type: Easing.InOutQuad; duration: 200 }
        NumberAnimation { target: [page1buttonHeader, page2buttonHeader]; properties: "anchors.leftMargin"; easing.type: Easing.InOutQuad; duration: 400 }
        NumberAnimation { target: [page1buttonInfo, page2buttonInfo]; properties: "opacity"; easing.type: Easing.InOutQuad; duration: 400 }
        NumberAnimation { target: [page1buttonInfo, page2buttonInfo]; properties: "anchors.rightMargin"; easing.type: Easing.OutQuad; duration: 800 }
    }

    Timer {
        interval: 10000
        onTriggered: switchPage(2-pageNum)
        running: true
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

                Image {
                    id: vigilanceSign
                    anchors.leftMargin: 15
                    anchors.topMargin: 15
                    anchors.left: parent.left
                    anchors.top: parent.top
                    source: "Slices/VigilanceSign.png"

                    state: stateView.IsVigilanceRequired ? "On" : "Off"
                    states: [
                        State {
                            name: "On"
                        },
                        State {
                            name: "Off"
                            PropertyChanges { target: vigilanceSign; opacity: 0.005; anchors.topMargin: 5 }
                        }
                    ]
                    transitions: Transition {
                        NumberAnimation { target: vigilanceSign; properties: "opacity"; easing.type: Easing.OutQuad; duration: 150 }
                        NumberAnimation { target: vigilanceSign; properties: "anchors.topMargin"; easing.type: Easing.OutElastic; duration: 700 }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: stateView.IsVigilanceRequired = !stateView.IsVigilanceRequired;
                    }
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

            Rectangle {
                id: page2container
                height: pagesArea.height
                color: "#6b6b6b"
//                gradient: Gradient {
//                    GradientStop {
//                        position: 0
//                        color: "#6b6b6b"
//                    }

//                    GradientStop {
//                        position: 1
//                        color: "#2b2b2b"
//                    }
//                }
                anchors.right: parent.right
                anchors.left: parent.left

                Text {
                    id: text2
                    color: "#ffffff"
                    text: qsTr("Состояние системы")
                    anchors.topMargin: 10
                    horizontalAlignment: Text.AlignHCenter
                    anchors.right: parent.right
                    anchors.left: parent.left
                    anchors.top: parent.top
                    font.pixelSize: 24
                    font.family: "URW Gothic L"
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

        width: 144
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

            Rectangle {
                x: panelLeft.width
                y: 0
                width: 7
                height: rootRect.height - speedBox.height
                color: "#fff"
                anchors.top: parent.top

                Behavior on height { SmoothedAnimation { duration: 500 } }
            }

            Rectangle {
                id: speedValueBar
                x: panelLeft.width
                width: 7
                height: (stateView.Speed/maxSpeed)*(rootRect.height - restrictionBox.height - speedBox.height)
                color: "#4999c9"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: speedBox.height

                Behavior on height { SmoothedAnimation { duration: 500 } }
            }

            Rectangle {
                id: restrictionBar
                x: panelLeft.width
                y: 0
                width: 7
                height: (rootRect.height - speedBox.height) - (stateView.SpeedRestriction/maxSpeed)*(rootRect.height - restrictionBox.height - speedBox.height)
                color: "#c94949"
                anchors.top: parent.top

                Behavior on height { SmoothedAnimation { duration: 500 } }
            }
        }

        Rectangle {
            height: 108
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 0
            color: "#00000000"
            anchors.rightMargin: 10
            anchors.right: parent.right
            id: restrictionBox
            x: 0
            y: 0
            width: 134

            Repeater {
                model: [ "#6c000000", "#c94949" ]

                Column {
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: index
                    anchors.right: parent.right
                    anchors.rightMargin: index

                    Text {
                        text: stateView.SpeedRestriction
                        anchors.right: parent.right
                        color: modelData
                        font.pointSize: 51.2
                        font.family: "URW Gothic L"
                        font.bold: true
                        height: 62
                    }
                    Text {
                        text: qsTr("км/ч ")
                        anchors.right: parent.right
                        color: modelData
                        font.pointSize: 14.4
                        font.family: "URW Gothic L"
                        font.bold: true
                    }
                }
            }
        }

        Rectangle {
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.rightMargin: 15
            width: 70
            height: 63
            color: "#00000000"
            id: speedBox
            x: 66
            y: 417
            Repeater {
                model: [ "#ff30759e", "#d8ffffff" ]
                Column {
                    y: index
                    anchors.right: parent.right
                    anchors.rightMargin: 1-index

                    Text {
                        text: Math.round(stateView.Speed)
                        anchors.right: parent.right
                        height: 38
                        color: modelData
                        font.pointSize: 26
                        font.family: "URW Gothic L"
                        font.bold: true
                    }
                    Text {
                        text: qsTr("км/ч ")
                        anchors.right: parent.right
                        color: modelData
                        font.pointSize: 11.2
                        font.family: "URW Gothic L"
                        font.bold: true
                    }
                }
            }
        }



        Rectangle {
            id: graduateBar

            width: 10

            color: "#00000000"
            anchors.top: parent.top
            anchors.topMargin: restrictionBox.height
            anchors.bottom: parent.bottom
            anchors.bottomMargin: speedBox.height
            anchors.right: parent.right

            Repeater
            {
                id: repeater
                model: Math.floor(maxSpeed/20) - 1
                Row {
                    property int sp: (index + 1) * 20
                    anchors.right: parent.right
                    height: 14;
                    y: graduateBar.height - (graduateBar.height / maxSpeed) * sp - height/2
                    //opacity: stateView.SpeedRestriction >= sp ? 1 : 0
                    spacing: 2

                    Rectangle {
                        anchors.verticalCenter: parent.verticalCenter
                        height: parent.height
                        width: 20
                        color: "#00000000"

                        Repeater {
                            model: [ "#71000000", "#a8ffffff" ]
                            Text { text: parent.parent.sp; font.family: "URW Gothic L"; font.pointSize: 10; font.bold: true
                                anchors.verticalCenterOffset: index-1
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                                anchors.rightMargin: 1-index
                                color: modelData }
                        }
                    }

                    Rectangle { anchors.verticalCenter: parent.verticalCenter; height: 1; color: "#000000";
                                width: 4 + Math.floor( index / repeater.count * 6); }
                }
            }
        }

        ListView {
            id: lightsPanel
            x: 7
            y: 123
            width: 54
            height: 280
            anchors.horizontalCenterOffset: -21
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

        // Очень плохо, что это здесь находится!!!
        Image {
            id: alsnSwitchBackgroundCircle
            anchors.left: parent.right
            anchors.leftMargin: -60
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
            source: "Slices/Panel-Right-Middle.png"
        }

        Rectangle {
            width: 6
            color: "#4999c9"
            anchors.left: parent.left
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
                    anchors.right: alsnSwitch.left
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
                    anchors.left: parent.right
                    anchors.leftMargin: -60
                    width: alsnSwitchBackgroundCircle.width
                    height: alsnSwitchBackgroundCircle.height

                    property real radius: 102
                    property real angle: 15
                    property string objColor: "#ffdddddd"

                    Repeater
                    {
                        model: [25, 50, 75]

                        Rectangle {
                            property real myRot: (1 - index) * alsnSwitch.angle
                            property int freq: modelData

                            x: alsnSwitch.width/2 - alsnSwitch.radius * Math.cos(myRot / 180 * Math.PI)
                            y: alsnSwitch.height/2 - alsnSwitch.radius * Math.sin(myRot / 180 * Math.PI)
                            rotation: myRot

                            color: alsnSwitch.objColor
                            width: 2
                            height: 2
                            smooth: true

                            Text {
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.right
                                anchors.leftMargin: 6

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

//                Row {
//                    spacing: 5
//                    anchors.top: parent.top
//                    anchors.topMargin: 20
//                    anchors.bottom: parent.bottom
//                    anchors.bottomMargin: 20
//                    anchors.left: parent.left
//                    anchors.leftMargin: 15

//                    Column {
//                        anchors.top: parent.top
//                        anchors.topMargin: 0
//                        anchors.bottom: parent.bottom
//                        anchors.bottomMargin: 0
//                        Text {
//                            text: qsTr("25")
//                            font.pointSize: 10
//                            font.family: "URW Gothic L"
//                            verticalAlignment: Text.AlignVCenter
//                            color: "#ffffff"
//                            height: parent.height/3
//                        }
//                        Text {
//                            text: qsTr("50")
//                            font.pointSize: 10
//                            font.family: "URW Gothic L"
//                            verticalAlignment: Text.AlignVCenter
//                            color: "#ffffff"
//                            height: parent.height/3
//                        }
//                        Text {
//                            text: qsTr("75")
//                            font.pointSize: 10
//                            font.family: "URW Gothic L"
//                            verticalAlignment: Text.AlignVCenter
//                            color: "#ffffff"
//                            height: parent.height/3
//                        }
//                    }

//                    Rectangle {
//                        id: alsnSelector
//                        width: 20
//                        color: "#00000000"
//                        radius: 8
//                        border.width: 2
//                        border.color: "#ffffff"
//                        anchors.bottom: parent.bottom
//                        anchors.bottomMargin: 3
//                        anchors.top: parent.top
//                        anchors.topMargin: 3

//                        Rectangle {
//                            id: alsnSelectorMarker
//                            x: 2
//                            y: 2
//                            width: 16
//                            height: 16
//                            color: "#ffffff"
//                            radius: 8
//                            anchors.horizontalCenter: parent.horizontalCenter
//                            MouseArea {
//                                anchors.fill: parent
//                                drag.target: parent; drag.axis: Drag.YAxis; drag.minimumY: 2; drag.maximumY: parent.parent.height - parent.height - 2;
//                                onReleased: refreshAlsnState();
//                            }
//                        }

//                        states: [
//                            State {
//                                name: "alsn0"
//                                when: (stateView.alsnFreq != 25 && tateView.alsnFreq != 50 && tateView.alsnFreq != 75)
//                                PropertyChanges { target: alsnSelectorMarker; opacity: 0.2 }
//                            },
//                            State {
//                                name: "alsn25"
//                                when: (stateView.alsnFreq == 25)
//                                PropertyChanges { target: alsnSelectorMarker; y: 0.5*(alsnSelector.height)/3 - 0.5*alsnSelectorMarker.height }
//                            },
//                            State {
//                                name: "alsn50"
//                                when: (stateView.alsnFreq == 50)
//                                PropertyChanges { target: alsnSelectorMarker; y: 1.5*(alsnSelector.height)/3 - 0.5*alsnSelectorMarker.height }
//                            },
//                            State {
//                                name: "alsn75"
//                                when: (stateView.alsnFreq == 75)
//                                PropertyChanges { target: alsnSelectorMarker; y: 2.5*(alsnSelector.height)/3 - 0.5*alsnSelectorMarker.height }
//                            }
//                        ]

//                        transitions: Transition {
//                            NumberAnimation { target: alsnSelectorMarker; properties: "y"; easing.type: Easing.InOutQuad; duration: 200 }
//                        }
//                    }
//                }
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
                    anchors.left: parent.left
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
                    anchors.left: parent.left
                    anchors.leftMargin: 25
                    anchors.verticalCenter: parent.verticalCenter

                    Text {
                        color: "#ffffff"
                        text: qsTr("Текущее")
                        font.pointSize: 20
                        font.family: "URW Gothic L"
                    }

                    Row {
                        id: page1buttonInfo
                        spacing: 2
                        anchors.right: parent.right
                        Text {
                            color: "#4999c9"
                            text: Math.round(stateView.Speed)
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
                        anchors.left: parent.left
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: -3
                        anchors.top: parent.top
                        anchors.topMargin: 1
                    }
                    Column {
                        id: page2buttonHeader
                        x: 25
                        y: 32
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                        anchors.left: parent.left
                        anchors.leftMargin: 25
                        anchors.verticalCenter: parent.verticalCenter

                        Text {
                            color: "#ffffff"
                            text: qsTr("Система")
                            font.pointSize: 20
                            font.family: "URW Gothic L"
                        }

                        Row {
                            id: page2buttonInfo
                            spacing: 3
                            anchors.right: parent.right

                            Image {
                                source: stateView.FullSetWarningLevel == 0 ? "Slices/FullSet-Small-Ok.png" :
                                                                             stateView.FullSetWarningLevel == 1 ?
                                                                                 "Slices/FullSet-Small-Warning.png" :
                                                                                 "Slices/FullSet-Small-Error.png"
                            }
                            Image {
                                source: stateView.IsPressureOk ? "Slices/Pressure-Small-Ok.png" : "Slices/Pressure-Small-Warning.png"
                            }
                            Image {
                                source: stateView.IsEpvReleased ? "Slices/Epv-Small-Warning.png" :
                                                                  stateView.IsEpvReady ?
                                                                      "Slices/Epv-Small-Ok.png" :
                                                                      "Slices/Epv-Small-NotReady.png"
                            }
                            Image {
                                source: stateView.SystemWarningLevel == 0 ? "Slices/System-Medium-Ok.png" :
                                                                             stateView.SystemWarningLevel == 1 ?
                                                                                 "Slices/System-Medium-Warning.png" :
                                                                                 "Slices/System-Medium-Error.png"
                            }
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

}
