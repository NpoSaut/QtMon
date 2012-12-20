import QtQuick 1.1
import views 1.0

Rectangle {
    width: 800
    height: 480
    id: rootRect

    state: "page1"

    property int pageNum: 1

    property double maxSpeed: 80

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

    Image {
        source: "Slices/all.png"
    }

//    SystemStateView {
//        id: stateView
//        objectName: "stateView"
//    }


//    states: [
//        State {
//            name: "page1"
//            when: (stateView.PropertyView == false)
//            PropertyChanges { target: page1indicator; width: 12 }
//            PropertyChanges { target: page2indicator; width: 6 }
//            PropertyChanges { target: pagesContainer; y: 0 }

//            PropertyChanges { target: page1buttonHeader; anchors.leftMargin: 22 }
//            PropertyChanges { target: page1buttonInfo; anchors.rightMargin: -20; opacity: 0.0 }
//        },
//        State {
//            name: "page2"
//            when: (stateView.PropertyView == true)
//            PropertyChanges { target: page1indicator; width: 6 }
//            PropertyChanges { target: page2indicator; width: 12 }
//            PropertyChanges { target: pagesContainer; y: -480 }

//            PropertyChanges { target: page2buttonHeader; anchors.leftMargin: 22 }
//            PropertyChanges { target: page2buttonInfo; anchors.rightMargin: -20; opacity: 0.00 }
//        }
//    ]

//    transitions: Transition {
//        NumberAnimation { target: pagesContainer; properties: "y"; easing.type: Easing.InOutQuad; duration: 500 }
//        NumberAnimation { targets: [page1indicator, page2indicator]; properties: "width"; easing.type: Easing.InOutQuad; duration: 200 }
//        NumberAnimation { target: [page1buttonHeader, page2buttonHeader]; properties: "anchors.leftMargin"; easing.type: Easing.InOutQuad; duration: 400 }
//        NumberAnimation { target: [page1buttonInfo, page2buttonInfo]; properties: "opacity"; easing.type: Easing.InOutQuad; duration: 400 }
//        NumberAnimation { target: [page1buttonInfo, page2buttonInfo]; properties: "anchors.rightMargin"; easing.type: Easing.OutQuad; duration: 800 }
//    }

//    Rectangle {
//        id: pagesArea
//        color: "#00000000"
//        anchors.bottom: parent.bottom
//        anchors.top: parent.top
//        anchors.right: parent.right
//        anchors.rightMargin: 149
//        anchors.left: parent.left
//        anchors.leftMargin: 151

//        Column {
//            id: pagesContainer
//            anchors.right: parent.right
//            anchors.left: parent.left
//            Rectangle {
//                id: page1container
//                height: 480
//                color: "#00000000"
//                anchors.right: parent.right
//                anchors.left: parent.left
//                anchors.leftMargin: 0
//                clip: true

//                Image {
//                    property double leftCoordinate: 60.226
//                    property double topCoordinate: 56.942
//                    property double rightCoordinate: 60.561
//                    property double bottomCoordinate: 56.791

//                    property double horizontalDensity: width/(rightCoordinate - leftCoordinate)
//                    property double verticalDensity: height/(bottomCoordinate - topCoordinate)


//                    x: (leftCoordinate -stateView.Longitude)*horizontalDensity + page1container.width/2
//                    y: (topCoordinate - stateView.Latitude)*verticalDensity + page1container.height/2

//                    Behavior on x { SmoothedAnimation { duration: 500 } }
//                    Behavior on y { SmoothedAnimation { duration: 500 } }

//                    source: "Slices/map.png"
//                    asynchronous: true

////                    MouseArea {
////                        enabled: false
////                        anchors.fill: parent
////                        drag.target: parent; drag.axis: Drag.XandYAxis;
////                    }
//                }

//                Image {
//                    x: 534
//                    y: 364
//                    anchors.verticalCenter: parent.verticalCenter
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    source: "Slices/Cross.png"
//                }

//                Rectangle {
//                    y: parent.height - speedValueBar.height - height/2
//                    width: 60
//                    height: 48
//                    color: "#00000000"
//                    anchors.left: parent.left

//                    Behavior on y { SmoothedAnimation { duration: 500 } }

//                    Rectangle {
//                        x: 6
//                        y: -6
//                        gradient: Gradient {
//                            GradientStop {
//                                position: 0
//                                color: "#b4ffffff"
//                            }

//                            GradientStop {
//                                position: 1
//                                color: "#00ffffff"
//                            }
//                        }
//                        width: parent.height
//                        height: parent.width
//                        anchors.horizontalCenter: parent.horizontalCenter
//                        anchors.verticalCenter: parent.verticalCenter
//                        rotation: -90
//                    }

//                    Column {
//                        anchors.fill: parent

//                        Text {
//                            id: speedValueLabel
//                            color: "#4999c9"
//                            text: stateView.Speed
//                            anchors.horizontalCenter: parent.horizontalCenter
//                            font.pixelSize: 26
//                            font.family: "URW Gothic L"
//                        }
//                        Text {
//                            color: "#4999c9"
//                            text: qsTr("км/ч")
//                            anchors.horizontalCenter: parent.horizontalCenter
//                            font.pixelSize: 12
//                            font.family: "URW Gothic L"
//                        }
//                    }
//                }

//                Image {
//                    id: vigilanceSign
//                    anchors.leftMargin: 15
//                    anchors.topMargin: 15
//                    anchors.left: parent.left
//                    anchors.top: parent.top
//                    source: "Slices/VigilanceSign.png"

//                    state: stateView.IsVigilanceRequired ? "On" : "Off"
//                    states: [
//                        State {
//                            name: "On"
//                        },
//                        State {
//                            name: "Off"
//                            PropertyChanges { target: vigilanceSign; opacity: 0.005; anchors.topMargin: 5 }
//                        }
//                    ]
//                    transitions: Transition {
//                        NumberAnimation { target: vigilanceSign; properties: "opacity"; easing.type: Easing.OutQuad; duration: 150 }
//                        NumberAnimation { target: vigilanceSign; properties: "anchors.topMargin"; easing.type: Easing.OutElastic; duration: 700 }
//                    }

//                    MouseArea {
//                        anchors.fill: parent
//                        onClicked: stateView.IsVigilanceRequired = !stateView.IsVigilanceRequired;
//                    }
//                }
//            }

//            Rectangle {
//                id: rectangle1
//                height: 480
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
//                anchors.right: parent.right
//                anchors.left: parent.left

//                Text {
//                    id: text2
//                    color: "#ffffff"
//                    text: qsTr("Состояние системы")
//                    anchors.topMargin: 10
//                    horizontalAlignment: Text.AlignHCenter
//                    anchors.right: parent.right
//                    anchors.left: parent.left
//                    anchors.top: parent.top
//                    font.pixelSize: 24
//                    font.family: "URW Gothic L"
//                }
//            }
//        }
//        MouseArea {
//            id: mousearea1
//            enabled: false
//            anchors.fill: parent
//            onPressed: swipePressed(mouseY)
//            onReleased: swipeReleased(mouseY)
//        }
//    }



//    Rectangle {
//        width: 145
//        height: 480
//        color: "#00000000"
//        anchors.left: parent.left
//        anchors.bottom: parent.bottom
//        anchors.top: parent.top

//        Image {
//            id: image2
//            anchors.left: parent.left
//            anchors.bottom: parent.bottom
//            anchors.top: parent.top
//            source: "Slices/Panel-Left.png"

//            Rectangle {
//                id: speedValueBar
//                x: 145
//                y: 280
//                width: 7
//                height: (stateView.Speed/maxSpeed)*(rootRect.height - restrictionBox.height)
//                color: "#4999c9"
//                anchors.bottom: parent.bottom

//                Behavior on height { SmoothedAnimation { duration: 500 } }
//            }

//            Rectangle {
//                id: restrictionBar
//                x: 145
//                y: 0
//                width: 7
//                height: rootRect.height - (stateView.SpeedRestriction/maxSpeed)*(rootRect.height - restrictionBox.height)
//                color: "#c94949"
//                anchors.topMargin: 0
//                anchors.top: parent.top

//                Behavior on height { SmoothedAnimation { duration: 500 } }
//            }


//        }

//        Column {
//            id: restrictionBox
//            x: 7
//            y: 0
//            height: 120
//            anchors.right: parent.right
//            anchors.rightMargin: 5
//            anchors.left: parent.left
//            anchors.leftMargin: 5

//            Text {
//                height: 15
//                color: "#c94949"
//                text: qsTr("ограничение")
//                font.pixelSize: 18
//                font.family: "URW Gothic L"
////                font.bold: true
//            }
//            Text {
//                height: 10
//                color: "#c94949"
//                text: qsTr("скорости")
//                font.pixelSize: 18
//                font.family: "URW Gothic L"
////                font.bold: true
//            }
//            Text {
//                height: 66
//                //x: -780
//                //y: 20
//                color: "#c94949"
//                text: stateView.SpeedRestriction
//                smooth: false
//                anchors.right: parent.right
//                horizontalAlignment: Text.AlignLeft
//                font.pixelSize: 64
//                font.family: "URW Gothic L"
////                font.bold: true
//            }
//            Text {
//                color: "#c94949"
//                text: qsTr("км/ч ")
//                anchors.right: parent.right
//                font.pixelSize: 18
//                font.family: "URW Gothic L"
//                font.bold: true
//            }
//        }

//        Rectangle {
//            x: 0
//            y: 120
//            height: 360
//            color: "#00000000"
//            anchors.bottom: parent.bottom
//            anchors.bottomMargin: 0
//            anchors.right: parent.right
//            anchors.left: parent.left
//            anchors.leftMargin: 0






//            ListView {
//                id: lightsPanel
//                width: 126
//                height: 282
//                interactive: false
//                //interactive: false
//                anchors.verticalCenter: parent.verticalCenter
//                anchors.horizontalCenter: parent.horizontalCenter
//                focus: true

//                currentIndex: 2

//                highlight: Rectangle { color: "lightsteelblue"; radius: 5 }

//                delegate: Item {
//                    height: 52

//                    Rectangle {
//                        id: wrapper
//                        width: 116
//                        height: 52
//                        color: "#00000000"
//                        Image {
//                            id: lightOffImage
//                            source: "Slices/Light-Off.png"
//                        }
//                        Image {
//                            id: lightOnImage
//                            source: "Slices/Light-" + name + ".png"
//                            opacity: 0
//                        }

//                        state: lightState

//                        states: [
//                            State {
//                                name: "On"
//                                PropertyChanges { target: lightOnImage; opacity: 1 }
//                                PropertyChanges { target: lightOffImage; opacity: 0 }
//                            },
//                            State {
//                                name: "Off"
//                            }
//                        ]

//                        transitions: Transition {
//                            NumberAnimation { targets: [lightOnImage, lightOffImage]; properties: "opacity"; easing.type: Easing.InOutQuad; duration: 200 }
//                        }
//                    }
//                }
//                model: ListModel {
//                    ListElement {
//                        name: "Green1"
//                        lightState: "On"
//                    }
//                    ListElement {
//                        name: "Yellow"
//                        lightState: "Off"
//                    }
//                    ListElement {
//                        name: "YellowRed"
//                        lightState: "On"
//                    }
//                    ListElement {
//                        name: "Red"
//                        lightState: "Off"
//                    }
//                    ListElement {
//                        name: "White"
//                        lightState: "Off"
//                    }
//                }

//                states: [
//                    State {
//                        name: "Green1"
//                        PropertyChanges { target: lightOnImage; opacity: 1 }
//                        PropertyChanges { target: lightOffImage; opacity: 0 }
//                    }
//                ]
//            }



//        }
//    }

//    Rectangle {
//        x: 652
//        y: 0
//        width: 149
//        height: 480
//        color: "#00000000"
//        anchors.bottom: parent.bottom
//        anchors.right: parent.right
//        anchors.top: parent.top

//        Image {
//            anchors.top: parent.top
//            anchors.bottom: parent.bottom
//            anchors.right: parent.right
//            source: "Slices/Panel-Right.png"
//        }

//        Image {
//            x: -14
//            y: 104
//            anchors.right: parent.right
//            anchors.verticalCenter: parent.verticalCenter
//            source: "Slices/Panel-Right-Middle.png"
//        }

//        Column {
//            x: -6
//            y: 0
//            anchors.fill: parent

//            Rectangle {
//                id: rectangle2
//                height: 120
//                color: "#00000000"
//                anchors.right: parent.right
//                anchors.left: parent.left
//                Rectangle {
//                    width: 6
//                    color: "#4999c9"
//                    anchors.left: parent.left
//                    anchors.bottom: parent.bottom
//                    anchors.top: parent.top
//                }

//                Text {
//                    id: text1
//                    y: 63
//                    color: "#ffffff"
//                    text: qsTr("АЛСН")
//                    anchors.left: parent.left
//                    anchors.leftMargin: 60
//                    anchors.verticalCenter: parent.verticalCenter
//                    font.pixelSize: 25
//                    font.family: "URW Gothic L"
//                }

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
//                                PropertyChanges { target: alsnSelectorMarker; opacity: 0.2 }
//                            },
//                            State {
//                                name: "alsn25"
//                                PropertyChanges { target: alsnSelectorMarker; y: 0.5*(alsnSelector.height)/3 - 0.5*alsnSelectorMarker.height }
//                            },
//                            State {
//                                name: "alsn50"
//                                PropertyChanges { target: alsnSelectorMarker; y: 1.5*(alsnSelector.height)/3 - 0.5*alsnSelectorMarker.height }
//                            },
//                            State {
//                                name: "alsn75"
//                                PropertyChanges { target: alsnSelectorMarker; y: 2.5*(alsnSelector.height)/3 - 0.5*alsnSelectorMarker.height }
//                            }
//                        ]

//                        transitions: Transition {
//                            NumberAnimation { target: alsnSelectorMarker; properties: "y"; easing.type: Easing.InOutQuad; duration: 200 }
//                        }
//                    }
//                }
//            }

//            Rectangle {
//                id: rectangle4
//                x: 0
//                y: 240
//                height: 120
//                color: "#00000000"
//                anchors.right: parent.right
//                anchors.left: parent.left
//                Rectangle {
//                    id: page1indicator
//                    width: 6
//                    color: "#4999c9"
//                    anchors.left: parent.left
//                    anchors.bottom: parent.bottom
//                    anchors.top: parent.top
//                }

//                Column {
//                    id: page1buttonHeader
//                    x: 25
//                    y: 32
//                    anchors.right: parent.right
//                    anchors.rightMargin: 10
//                    anchors.left: parent.left
//                    anchors.leftMargin: 25
//                    anchors.verticalCenter: parent.verticalCenter

//                    Text {
//                        color: "#ffffff"
//                        text: qsTr("Текущее")
//                        font.pointSize: 20
//                        font.family: "URW Gothic L"
//                    }

//                    Row {
//                        id: page1buttonInfo
//                        spacing: 2
//                        anchors.right: parent.right
//                        Text {
//                            color: "#4999c9"
//                            text: stateView.Speed
//                            anchors.bottom: parent.bottom
////                            font.bold: true
//                            font.pointSize: 17
//                            font.family: "URW Gothic L"
//                        }
//                        Text {
//                            color: "#ffffff"
//                            text: qsTr("/")
//                            anchors.bottom: parent.bottom
////                            font.bold: true
//                            font.pointSize: 14
//                            font.family: "URW Gothic L"
//                        }
//                        Text {
//                            color: "#c94949"
//                            text: stateView.SpeedRestriction
//                            anchors.bottom: parent.bottom
////                            font.bold: true
//                            font.pointSize: 14
//                            font.family: "URW Gothic L"
//                        }
//                        }
//                }
//                MouseArea {
//                    anchors.fill: parent
//                    onPressed: switchPage(1)
//                }
//            }
//            Rectangle {
//                id: rectangle3
//                    x: 0
//                    y: 120
//                    height: 120
//                    color: "#00000000"
//                    anchors.right: parent.right
//                    anchors.left: parent.left

//                    Rectangle {
//                        id: page2indicator
//                        width: 6
//                        color: "#4999c9"
//                        anchors.left: parent.left
//                        anchors.bottom: parent.bottom
//                        anchors.top: parent.top
//                    }
//                    Column {
//                        id: page2buttonHeader
//                        x: 25
//                        y: 32
//                        anchors.right: parent.right
//                        anchors.rightMargin: 10
//                        anchors.left: parent.left
//                        anchors.leftMargin: 25
//                        anchors.verticalCenter: parent.verticalCenter

//                        Text {
//                            color: "#ffffff"
//                            text: qsTr("Система")
//                            font.pointSize: 20
//                            font.family: "URW Gothic L"
//                        }

//                        Row {
//                            id: page2buttonInfo
//                            spacing: 3
//                            anchors.right: parent.right

//                            Image {
//                                source: stateView.FullSetWarningLevel == 0 ? "Slices/FullSet-Small-Ok.png" :
//                                                                             stateView.FullSetWarningLevel == 1 ?
//                                                                                 "Slices/FullSet-Small-Warning.png" :
//                                                                                 "Slices/FullSet-Small-Error.png"
//                            }
//                            Image {
//                                source: stateView.IsPressureOk ? "Slices/Pressure-Small-Ok.png" : "Slices/Pressure-Small-Warning.png"
//                            }
//                            Image {
//                                source: stateView.IsEpvReleased ? "Slices/Epv-Small-Warning.png" :
//                                                                  stateView.IsEpvReady ?
//                                                                      "Slices/Epv-Small-Ok.png" :
//                                                                      "Slices/Epv-Small-NotReady.png"
//                            }
//                            Image {
//                                source: stateView.SystemWarningLevel == 0 ? "Slices/System-Medium-Ok.png" :
//                                                                             stateView.SystemWarningLevel == 1 ?
//                                                                                 "Slices/System-Medium-Warning.png" :
//                                                                                 "Slices/System-Medium-Error.png"
//                            }
//                        }
//                    }
//                    MouseArea {
//                        anchors.fill: parent
//                        onPressed: switchPage(2)
//                    }
//            }

//            Rectangle {
//                height: 120
//                color: "#00000000"
//                anchors.right: parent.right
//                anchors.left: parent.left
//                Rectangle {
//                    width: 6
//                    color: "#4999c9"
//                    anchors.left: parent.left
//                    anchors.bottom: parent.bottom
//                    anchors.top: parent.top
//                }
//            }

//        }

//    }

}
