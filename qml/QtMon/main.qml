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
                            }
                            Column
                            {
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.verticalCenter: parent.verticalCenter
                                Text {
                                    color: "#ff00f7"
                                    text: index
                                    font.bold: true
                                }
                                Text {
                                    color: "#ff00f7"
                                    text: parent.parent.relativeHorizontalIndex + "  " + parent.parent.relativeVerticalIndex
                                }
                                Text {
                                    color: "#ff00f7"
                                    text: parent.parent.horizontalIndex + "  " + parent.parent.verticalIndex
                                }
                            }

                            //Behavior on x { SmoothedAnimation { duration: 1000 } }
                            //Behavior on y { SmoothedAnimation { duration: 1000 } }
                        }
                    }


                }
                Text {
                    color: "#00428d"
                    font.pointSize: 14
                    text: "Center: " + mapContainer.currentHorizontalIndex + "  " + mapContainer.currentVerticalIndex
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
                    id: graduateBar

                    x: -2
                    y: 0
                    width: 10
                    height: rootRect.height

                    color: "#00000000"

                    Rectangle {
                        property int sp: 10
                        y: rootRect.height - (rootRect.height - restrictionBox.height) / maxSpeed * sp - 8
                        color: stateView.SpeedRestriction >= sp ? "#505050" : "#00000000"

                        Rectangle { x:0; y: 8; height: 2; width: 10; color: parent.color }
                        Text { x: 10; y: 0; text: parent.sp; font.family: "URW Gothic L"; font.pixelSize: 14;
                            color: stateView.SpeedRestriction >= parent.sp ? "#2d2d2d" : "#00000000" }
                    }
                    Rectangle {
                        property int sp: 20
                        y: rootRect.height - (rootRect.height - restrictionBox.height) / maxSpeed * sp - 8
                        color: stateView.SpeedRestriction >= sp ? "#505050" : "#00000000"

                        Rectangle { x:0; y: 8; height: 2; width: 10; color: parent.color }
                        Text { x: 10; y: 0; text: parent.sp; font.family: "URW Gothic L"; font.pixelSize: 14;
                            color: stateView.SpeedRestriction >= parent.sp ? "#2d2d2d" : "#00000000" }
                    }
                    Rectangle {
                        property int sp: 30
                        y: rootRect.height - (rootRect.height - restrictionBox.height) / maxSpeed * sp - 8
                        color: stateView.SpeedRestriction >= sp ? "#505050" : "#00000000"

                        Rectangle { x:0; y: 8; height: 2; width: 10; color: parent.color }
                        Text { x: 10; y: 0; text: parent.sp; font.family: "URW Gothic L"; font.pixelSize: 14;
                            color: stateView.SpeedRestriction >= parent.sp ? "#2d2d2d" : "#00000000" }
                    }
                    Rectangle {
                        property int sp: 40
                        y: rootRect.height - (rootRect.height - restrictionBox.height) / maxSpeed * sp - 8
                        color: stateView.SpeedRestriction >= sp ? "#505050" : "#00000000"

                        Rectangle { x:0; y: 8; height: 2; width: 10; color: parent.color }
                        Text { x: 10; y: 0; text: parent.sp; font.family: "URW Gothic L"; font.pixelSize: 14;
                            color: stateView.SpeedRestriction >= parent.sp ? "#2d2d2d" : "#00000000" }
                    }
                    Rectangle {
                        property int sp: 50
                        y: rootRect.height - (rootRect.height - restrictionBox.height) / maxSpeed * sp - 8
                        color: stateView.SpeedRestriction >= sp ? "#505050" : "#00000000"

                        Rectangle { x:0; y: 8; height: 2; width: 10; color: parent.color }
                        Text { x: 10; y: 0; text: parent.sp; font.family: "URW Gothic L"; font.pixelSize: 14;
                            color: stateView.SpeedRestriction >= parent.sp ? "#2d2d2d" : "#00000000" }
                    }
                    Rectangle {
                        property int sp: 60
                        y: rootRect.height - (rootRect.height - restrictionBox.height) / maxSpeed * sp - 8
                        color: stateView.SpeedRestriction >= sp ? "#505050" : "#00000000"

                        Rectangle { x:0; y: 8; height: 2; width: 10; color: parent.color }
                        Text { x: 10; y: 0; text: parent.sp; font.family: "URW Gothic L"; font.pixelSize: 14;
                            color: stateView.SpeedRestriction >= parent.sp ? "#2d2d2d" : "#00000000" }
                    }
                    Rectangle {
                        property int sp: 70
                        y: rootRect.height - (rootRect.height - restrictionBox.height) / maxSpeed * sp - 8
                        color: stateView.SpeedRestriction >= sp ? "#505050" : "#00000000"

                        Rectangle { x:0; y: 8; height: 2; width: 10; color: parent.color }
                        Text { x: 10; y: 0; text: parent.sp; font.family: "URW Gothic L"; font.pixelSize: 14;
                            color: stateView.SpeedRestriction >= parent.sp ? "#2d2d2d" : "#00000000" }
                    }
                    Rectangle {
                        property int sp: 80
                        y: rootRect.height - (rootRect.height - restrictionBox.height) / maxSpeed * sp - 8
                        color: stateView.SpeedRestriction >= sp ? "#505050" : "#00000000"

                        Rectangle { x:0; y: 8; height: 2; width: 10; color: parent.color }
                        Text { x: 10; y: 0; text: parent.sp; font.family: "URW Gothic L"; font.pixelSize: 14;
                            color: stateView.SpeedRestriction >= parent.sp ? "#2d2d2d" : "#00000000" }
                    }
                    Rectangle {
                        property int sp: 90
                        y: rootRect.height - (rootRect.height - restrictionBox.height) / maxSpeed * sp - 8
                        color: stateView.SpeedRestriction >= sp ? "#505050" : "#00000000"

                        Rectangle { x:0; y: 8; height: 2; width: 10; color: parent.color }
                        Text { x: 10; y: 0; text: parent.sp; font.family: "URW Gothic L"; font.pixelSize: 14;
                            color: stateView.SpeedRestriction >= parent.sp ? "#2d2d2d" : "#00000000" }
                    }
                    Rectangle {
                        property int sp: 100
                        y: rootRect.height - (rootRect.height - restrictionBox.height) / maxSpeed * sp - 8
                        color: stateView.SpeedRestriction >= sp ? "#505050" : "#00000000"

                        Rectangle { x:0; y: 8; height: 2; width: 10; color: parent.color }
                        Text { x: 10; y: 0; text: parent.sp; font.family: "URW Gothic L"; font.pixelSize: 14;
                            color: stateView.SpeedRestriction >= parent.sp ? "#2d2d2d" : "#00000000" }
                    }
                }

                Rectangle {
                    id: hintBox

                    anchors.bottom: parent.bottom
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

                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 2
                        anchors.left: parent.left
                        anchors.leftMargin: 16

                        font.family: "URW Gothic L"; font.pixelSize: 14;
                        color: "#2d2d2d";
                    }

                    Text {
                        //text: stateView.Date;
                        text: qsTr("21 декабря 2012");

                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 2
                        anchors.horizontalCenter: parent.horizontalCenter

                        font.family: "URW Gothic L"; font.pixelSize: 14;
                        color: "#2d2d2d";
                    }

                    Text {
                        text: stateView.Milage + qsTr(" км");

                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 2
                        anchors.right: parent.right
                        anchors.rightMargin: 16

                        font.family: "URW Gothic L"; font.pixelSize: 14;
                        color: "#2d2d2d";
                    }
                }
            }

            Rectangle {
                id: page2container
                height: pagesArea.height
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
            id: mousearea1
            enabled: false
            anchors.fill: parent
            onPressed: swipePressed(mouseY)
            onReleased: swipeReleased(mouseY)
        }
    }



    Rectangle {
        id: panelLeft

        width: 145
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
                id: speedValueBar
                x: 144
                y: 280
                width: 7
                height: (stateView.Speed/maxSpeed)*(rootRect.height - restrictionBox.height)
                color: "#4999c9"
                anchors.bottom: parent.bottom

                Behavior on height { SmoothedAnimation { duration: 500 } }
            }

            Rectangle {
                id: speedValueSubBar
                x: 139
                y: 280
                width: 7
                height: 58
                color: "#4999c9"
                anchors.bottom: parent.bottom

                Behavior on height { SmoothedAnimation { duration: 500 } }
            }

            Rectangle {
                id: restrictionBar
                x: 144
                y: 0
                width: 7
                height: rootRect.height - (stateView.SpeedRestriction/maxSpeed)*(rootRect.height - restrictionBox.height)
                color: "#c94949"
                anchors.topMargin: 0
                anchors.top: parent.top

                Behavior on height { SmoothedAnimation { duration: 500 } }
            }

            Rectangle {
                id: restrictionSubBar
                x: 139
                y: 0
                width: 7
                height: 120
                color: "#c94949"
                anchors.topMargin: 0
                anchors.top: parent.top

                Behavior on height { SmoothedAnimation { duration: 500 } }
            }
        }

        Column {
            id: restrictionBox

            width: 140
            height: 120
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 3

            Text {
                text: qsTr("ограничение")

                anchors.horizontalCenter: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter
                height: 15

                color: "#d3a44c"
                font.pixelSize: 18
                font.family: "URW Gothic L"
//                font.bold: true
            }
            Text {
                text: qsTr("скорости")

                anchors.horizontalCenter: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter
                height: 10

                color: "#d3a44c"
                font.pixelSize: 18
                font.family: "URW Gothic L"
//                font.bold: true
            }
            Text {
                text: stateView.SpeedRestriction

                anchors.horizontalCenter: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter
                height: 66

                color: "#c94949"
                font.pixelSize: 64
                font.family: "URW Gothic L"
//                font.bold: true
            }
            Text {
                text: qsTr("км/ч ")

                anchors.horizontalCenter: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter

                color: "#c94949"
                font.pixelSize: 18
                font.family: "URW Gothic L"
                font.bold: true
            }
        }

        Column {
            id: speedBox

            width: 140
            height: 62 // ???
            anchors.bottom: parent.bottom
            anchors.left: parent.left

            Text {
                text: stateView.Speed

                anchors.horizontalCenter: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter
                height: 42

                color: "#4999c9"
                font.pixelSize: 40
                font.family: "URW Gothic L"
//                font.bold: true
            }
            Text {
                text: qsTr("км/ч ")

                anchors.horizontalCenter: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter

                color: "#4999c9"
                font.pixelSize: 14
                font.family: "URW Gothic L"
//                font.bold: true
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
            x: -14
            y: 104
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            source: "Slices/Panel-Right-Middle.png"
        }

        Column {
            x: -6
            y: 0
            anchors.fill: parent

            Rectangle {
                id: rectangle2
                height: 120
                color: "#00000000"
                anchors.right: parent.right
                anchors.left: parent.left
                Rectangle {
                    width: 6
                    color: "#4999c9"
                    anchors.left: parent.left
                    anchors.bottom: parent.bottom
                    anchors.top: parent.top
                }

                Text {
                    id: text1
                    y: 63
                    color: "#ffffff"
                    text: qsTr("АЛСН")
                    anchors.left: parent.left
                    anchors.leftMargin: 60
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 25
                    font.family: "URW Gothic L"
                }

                Row {
                    spacing: 5
                    anchors.top: parent.top
                    anchors.topMargin: 20
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 20
                    anchors.left: parent.left
                    anchors.leftMargin: 15

                    Column {
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        Text {
                            text: qsTr("25")
                            font.pointSize: 10
                            font.family: "URW Gothic L"
                            verticalAlignment: Text.AlignVCenter
                            color: "#ffffff"
                            height: parent.height/3
                        }
                        Text {
                            text: qsTr("50")
                            font.pointSize: 10
                            font.family: "URW Gothic L"
                            verticalAlignment: Text.AlignVCenter
                            color: "#ffffff"
                            height: parent.height/3
                        }
                        Text {
                            text: qsTr("75")
                            font.pointSize: 10
                            font.family: "URW Gothic L"
                            verticalAlignment: Text.AlignVCenter
                            color: "#ffffff"
                            height: parent.height/3
                        }
                    }

                    Rectangle {
                        id: alsnSelector
                        width: 20
                        color: "#00000000"
                        radius: 8
                        border.width: 2
                        border.color: "#ffffff"
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 3
                        anchors.top: parent.top
                        anchors.topMargin: 3

                        Rectangle {
                            id: alsnSelectorMarker
                            x: 2
                            y: 2
                            width: 16
                            height: 16
                            color: "#ffffff"
                            radius: 8
                            anchors.horizontalCenter: parent.horizontalCenter
                            MouseArea {
                                anchors.fill: parent
                                drag.target: parent; drag.axis: Drag.YAxis; drag.minimumY: 2; drag.maximumY: parent.parent.height - parent.height - 2;
                                onReleased: refreshAlsnState();
                            }
                        }

                        states: [
                            State {
                                name: "alsn0"
                                when: (stateView.alsnFreq != 25 && tateView.alsnFreq != 50 && tateView.alsnFreq != 75)
                                PropertyChanges { target: alsnSelectorMarker; opacity: 0.2 }
                            },
                            State {
                                name: "alsn25"
                                when: (stateView.alsnFreq == 25)
                                PropertyChanges { target: alsnSelectorMarker; y: 0.5*(alsnSelector.height)/3 - 0.5*alsnSelectorMarker.height }
                            },
                            State {
                                name: "alsn50"
                                when: (stateView.alsnFreq == 50)
                                PropertyChanges { target: alsnSelectorMarker; y: 1.5*(alsnSelector.height)/3 - 0.5*alsnSelectorMarker.height }
                            },
                            State {
                                name: "alsn75"
                                when: (stateView.alsnFreq == 75)
                                PropertyChanges { target: alsnSelectorMarker; y: 2.5*(alsnSelector.height)/3 - 0.5*alsnSelectorMarker.height }
                            }
                        ]

                        transitions: Transition {
                            NumberAnimation { target: alsnSelectorMarker; properties: "y"; easing.type: Easing.InOutQuad; duration: 200 }
                        }
                    }
                }
            }

            Rectangle {
                id: rectangle4
                x: 0
                y: 240
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
                    anchors.top: parent.top
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
                    x: 0
                    y: 0
                    anchors.rightMargin: 0
                    anchors.bottomMargin: 0
                    anchors.leftMargin: 0
                    anchors.topMargin: 0
                    anchors.fill: parent
                    onPressed: switchPage(1)
                }
            }
            Rectangle {
                id: rectangle3
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
                        anchors.top: parent.top
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
                height: 120
                color: "#00000000"
                anchors.right: parent.right
                anchors.left: parent.left
                Rectangle {
                    width: 6
                    color: "#4999c9"
                    anchors.left: parent.left
                    anchors.bottom: parent.bottom
                    anchors.top: parent.top
                }
            }

        }

    }

}
