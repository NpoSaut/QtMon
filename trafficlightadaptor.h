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
    void trafficlightChanged (int qmlLightCode);
    
public slots:
    void proccessNewTrafficlight (Trafficlight light);
};

#endif // TRAFFICLIGHTADAPTOR_H
