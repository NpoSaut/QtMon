#include "trafficlightadaptor.h"
#include "QMetaType"

TrafficlightAdaptor::TrafficlightAdaptor(QObject *parent) :
    QObject(parent)
{
    qRegisterMetaType<Trafficlight>("Trafficlight");
}


void TrafficlightAdaptor::proccessNewTrafficlight(Trafficlight light)
{
    emit trafficlightCodeChanged (int (light));

    switch (light) {
    case WHITE:
        emit trafficlightChanged(0);
        emit trafficlightUpStateChanged(true);
        emit freeBlockZonesNumberChanged(0);
        emit freeBlockZonesUpStateChanged(false);
        break;
    case RED:
        emit trafficlightChanged(1);
        emit trafficlightUpStateChanged(true);
        emit freeBlockZonesNumberChanged(0);
        emit freeBlockZonesUpStateChanged(false);
        break;
    case YELLOW_RED:
        emit trafficlightChanged(2);
        emit trafficlightUpStateChanged(true);
        emit freeBlockZonesNumberChanged(0);
        emit freeBlockZonesUpStateChanged(false);
        break;
    case YELLOW:
        emit trafficlightChanged(3);
        emit trafficlightUpStateChanged(true);
        emit freeBlockZonesNumberChanged(1);
        emit freeBlockZonesUpStateChanged(false);
        break;
    case GREEN:
        emit trafficlightChanged(4);
        emit trafficlightUpStateChanged(true);
        emit freeBlockZonesNumberChanged(2);
        emit freeBlockZonesUpStateChanged(false);
        break;
    case OFF:
        emit trafficlightChanged(0);
        emit trafficlightUpStateChanged(false);
        emit freeBlockZonesNumberChanged(0);
        emit freeBlockZonesUpStateChanged(false);
        break;
    case OFF1:
        emit trafficlightChanged(0);
        emit trafficlightUpStateChanged(false);
        emit freeBlockZonesNumberChanged(0);
        emit freeBlockZonesUpStateChanged(false);
        break;
    case OFF2:
        emit trafficlightChanged(0);
        emit trafficlightUpStateChanged(false);
        emit freeBlockZonesNumberChanged(0);
        emit freeBlockZonesUpStateChanged(false);
        break;
    case WHITE_BLINK:
        emit trafficlightChanged(0);
        emit trafficlightUpStateChanged(true);
        emit freeBlockZonesNumberChanged(0);
        emit freeBlockZonesUpStateChanged(false);
        break;
    case RED_EN:
        emit trafficlightChanged(1);
        emit trafficlightUpStateChanged(true);
        emit freeBlockZonesNumberChanged(0);
        emit freeBlockZonesUpStateChanged(false);
        break;
    case YELLOW_RED_EN:
        emit trafficlightChanged(2);
        emit trafficlightUpStateChanged(true);
        emit freeBlockZonesNumberChanged(0);
        emit freeBlockZonesUpStateChanged(false);
        break;
    case FREE_ZONE_1:
        emit trafficlightChanged(3);
        emit trafficlightUpStateChanged(true);
        emit freeBlockZonesNumberChanged(1);
        emit freeBlockZonesUpStateChanged(false);
        break;
    case FREE_ZONE_2:
        emit trafficlightChanged(4);
        emit trafficlightUpStateChanged(true);
        emit freeBlockZonesNumberChanged(2);
        emit freeBlockZonesUpStateChanged(false);
        break;
    case FREE_ZONE_3:
        emit trafficlightChanged(4);
        emit trafficlightUpStateChanged(true);
        emit freeBlockZonesNumberChanged(3);
        emit freeBlockZonesUpStateChanged(true);
        break;
    case FREE_ZONE_4:
        emit trafficlightChanged(4);
        emit trafficlightUpStateChanged(true);
        emit freeBlockZonesNumberChanged(4);
        emit freeBlockZonesUpStateChanged(true);
        break;
    case FREE_ZONE_5:
        emit trafficlightChanged(4);
        emit trafficlightUpStateChanged(true);
        emit freeBlockZonesNumberChanged(5);
        emit freeBlockZonesUpStateChanged(true);
        break;
    default:
        emit trafficlightChanged(0);
        emit trafficlightUpStateChanged(false);
        emit freeBlockZonesNumberChanged(0);
        emit freeBlockZonesUpStateChanged(false);
        break;
    }
}


TrafficLightOnOffAdaptor::TrafficLightOnOffAdaptor(QObject *parent)
    : TrafficlightAdaptor (parent), on (false), light (Trafficlight::OFF)
{ }

void TrafficLightOnOffAdaptor::proccessNewTrafficlight(Trafficlight trafficlight)
{
    light = trafficlight;
    sendToParent();
}

void TrafficLightOnOffAdaptor::setOnOffState(bool turnedOn)
{
    on = turnedOn;
    sendToParent();
}

void TrafficLightOnOffAdaptor::sendToParent()
{
    TrafficlightAdaptor::proccessNewTrafficlight(on ? light : Trafficlight::OFF);
}


