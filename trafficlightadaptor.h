#ifndef TRAFFICLIGHTADAPTOR_H
#define TRAFFICLIGHTADAPTOR_H

#include <QObject>
#include <qtBlokLib/parsers/trafficlight.h>

// Преобразует формат светофора к том, с чем может работать qml
class TrafficlightAdaptor : public QObject
{
    Q_OBJECT
public:
    explicit TrafficlightAdaptor(QObject *parent = 0);
    
signals:
    void trafficlightCodeChanged (int qmlLightCode);

    void trafficlightChanged (int light);
    void trafficlightUpStateChanged (bool lightUp);
    void freeBlockZonesNumberChanged (int freeZones);
    void freeBlockZonesUpStateChanged (bool indicatorUp);
    
public slots:
    virtual void proccessNewTrafficlight (Trafficlight light);
};

class TrafficLightOnOffAdaptor : public TrafficlightAdaptor
{
    Q_OBJECT
public:
    explicit TrafficLightOnOffAdaptor(QObject *parent = 0);

public slots:
    void proccessNewTrafficlight (Trafficlight trafficlight);
    void setOnState (bool turnedOn);

private:
    bool on;
    Trafficlight light;

    void sendToParent ();
};

#endif // TRAFFICLIGHTADAPTOR_H
