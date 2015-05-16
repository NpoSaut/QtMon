import CustomComponents 1.0
import QtQuick 1.1

Rectangle {
    id: root
    property color tickColor: "#0f0"
    property color tickLabelColor: tickColor
    property color needleColor: "#f00"
    property variant needleAccents: []
    property int tickLabelPixelSize: Math.max(8*Math.log(height/20), 12)
    property string fontFamily: undefined

    property double minValue: -12
    property double maxValue: 108
    property variant values: []

    property variant warnings: []

    property int minAngle: 90+135
    property int maxAngle: 90-135

    property double ticksDensity: 30
    property int smallTicksPerStep: 1

    property double step: 5 * (Math.pow(2, Math.floor(Math.log(Math.abs(root.maxValue - root.minValue) / ticksDensity) / Math.log(2))))

    property double floorValue: step * Math.floor(minValue/step)
    property double ceilValue: step * Math.ceil(maxValue/step)

    property int tickCount: Math.abs(ceilValue - floorValue) / step
    property double tickLabelOffset: (warnings.length === 0 ? 0 : 6) + 4 + tickLabelPixelSize * 0.7

    property double ringRadius: Math.min(width, height) * 0.05
    property double cutRadius: 0

    function restrict(val)
    {
        return Math.max(maxAngle - 8, Math.min(minAngle + 8, val))
    }

    function angle(val)
    {
        return minAngle + (val - floorValue) * (maxAngle - minAngle) / (ceilValue - floorValue)
    }

    color: "#00000000"

    // Шкала
    Rectangle {
        id: dial
        color: "#00000000"
        anchors.fill: root

        // Предупреждающие зоны
        Repeater {
            model: warnings

            Arc {
                penWidth: 2
                anchors.fill: parent
                anchors.margins: 6 + 0.1*tickLabelPixelSize
                startAngle: root.restrict(root.angle(modelData.minValue))
                endAngle: root.restrict(root.angle(modelData.maxValue))
                color: modelData.color
            }
        }

        // Дуги шкалы
        Repeater {
            model: root.tickCount

            Arc {
                penWidth: 2
                anchors.fill: parent
                startAngle: root.angle(root.floorValue + index * root.step)
                endAngle: root.angle(root.floorValue + (index + 1) * root.step) + Math.asin( 10.0 / root.width * 2 ) / 3.14 * 180
                color: root.tickColor
            }
        }

        // Подписи на засечках
        Repeater {
            model: root.tickCount + 1
            Text {
                property double val: root.floorValue + index * root.step
                color: root.tickLabelColor
                text: val
                font.pixelSize: root.tickLabelPixelSize
                font.family: fontFamily
                x: 0.5 * dial.width  + (0.5 * dial.width - root.tickLabelOffset) * Math.cos(root.angle(val) * 3.14/180.0) - 0.5 * width;
                y: 0.5 * dial.height - (0.5 * dial.height - root.tickLabelOffset) * Math.sin(root.angle(val) * 3.14/180.0) - 0.5 * height;
            }
        }

        // Тики (засечки)
        Repeater {
            model: root.tickCount * smallTicksPerStep + 1
            Rectangle {
                property double val: root.floorValue + index * root.step / smallTicksPerStep
                width: index % smallTicksPerStep === 0 ? 6 : 2.8
                height: width
                radius: width / 2
                color: index % smallTicksPerStep === 0 ? root.tickColor : "#000"
                x: dial.width  * (0.5 + 0.5 * Math.cos(root.angle(val) * 3.14/180.0)) - 0.5 * width
                y: dial.height * (0.5 - 0.5 * Math.sin(root.angle(val) * 3.14/180.0)) - 0.5 * height
            }
        }

    }

    // Стрелки
    Repeater {
        model: values
        Needle {
            penWidth: 6
            anchors.fill: parent
            anchors.margins: 5
            ringRadius: root.ringRadius
            cutRadius: root.cutRadius

            angle: root.restrict(root.angle(modelData))
            color: "#000"
            opacity: 0.5
        }
    }
    Repeater {
        model: values
        Needle {
            penWidth: 2
            anchors.fill: parent
            anchors.margins: 5
            ringRadius: root.ringRadius
            cutRadius: root.cutRadius

            angle: root.restrict(root.angle(modelData))
            color: needleColor
            fillColor: needleAccents.length <= index
                       ? "#00000000"
                       : needleAccents[index]
        }
    }

}
