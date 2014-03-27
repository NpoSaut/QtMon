#include "trafficlightadaptor.h"
#include "QMetaType"

TrafficlightAdaptor::TrafficlightAdaptor(QObject *parent) :
    QObject(parent)
{
    qRegisterMetaType<Trafficlight>("Trafficlight");
}


void TrafficlightAdaptor::proccessNewTrafficlight(Trafficlight light)
{
    int code;
    switch (light) {
    case RED:
    case RED_EN:
        code = 0;
        break;
    case YELLOW_RED:
    case YELLOW_RED_EN:
        code = 1;
        break;
    case YELLOW:
    case YELLOW_EN:
        code = 2;
        break;
    case GREEN:
    case GREEN_1_EN:
        code = 3;
        break;
    case GREEN_2_EN:
        code = 4;
        break;
    case GREEN_3_EN:
        code = 5;
        break;
    case GREEN_4_EN:
        code = 6;
        break;
    case WHITE:
    default:
        code = -1;
        break;
    }
    emit trafficlightChanged (code);
}
