#include "trafficlightadaptor.h"
#include "QMetaType"

TrafficlightAdaptor::TrafficlightAdaptor(QObject *parent) :
    QObject(parent)
{
    qRegisterMetaType<Trafficlight>("Trafficlight");
}


void TrafficlightAdaptor::proccessNewTrafficlight(Trafficlight light)
{
    emit trafficlightChanged (int (light));
}
