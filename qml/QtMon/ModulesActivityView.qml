import QtQuick 1.1
import views 1.0

Rectangle {
    id: root;
    property ModulesActivityViewModel model: modulesActivity;

    property color textColor: "#0f0"
    property color foreground: "#000"
    property color background: "#f00"
    property double fontHeight: 12

    height: column.height + 30
    width: column.width + 200

    color: background
    border.color: accentColor
    border.width: 1

    Column {
        id: column
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        Repeater {
            model: [
                { i: "1", text : "БС-ДПС", value : root.model.bsDpsActivity },
                { i: "2", text : "Монитор", value : root.model.monitorActivity },
                { i: "3", text : "ИПД", value : root.model.ipdActivity },
                { i: "4", text : "МП-АЛС", value : root.model.mpAlsActivity },
                { i: "5", text : "ЭК", value : root.model.electronicMapActivity },
                { i: "6", text : "GPS", value : root.model.gpsActivity },
                { i: "7", text : "УКТОЛ/ВДС", value : root.model.uktolOrVdsActivity },
                { i: "8", text : "САУТ", value : root.model.sautActivity },
                { i: "9", text : "РК/Шлюз CAN-MVB2", value : root.model.radioOrCanMvb2Activity },
                { i: "A", text : "ЭПК-151Д/Вывод", value : root.model.epk151dOrOutputActivity},
                { i: "B", text : "ТСКБМ-К", value : root.model.tskbmActivity },
                { i: "C", text : "МСУЛ", value : root.model.msulActivity }
            ]
            Row {
                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    color: modelData.value ? root.foreground : "#00000000"
                    height: root.fontHeight * 1.2
                    width: height

                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.pixelSize: root.fontHeight
                        color: modelData.value ? root.background : root.foreground
                        text: modelData.i
                        opacity: modelData.value ? 1.0 : 0.9
                    }
                }
                Rectangle {
                    width: root.fontHeight - 4
                    height: root.fontHeight + 6
                    color: "#00000000"
                }

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    color: root.textColor
                    font.pixelSize: root.fontHeight
                    text: modelData.text
                }
            }
        }
    }
}
