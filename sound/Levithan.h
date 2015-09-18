#ifndef LEVITHAN_H
#define LEVITHAN_H

#include <QObject>
#include "qtBlokLib/parsers/trafficlight.h"

class Levithan : public QObject
{
    Q_OBJECT
public:
    explicit Levithan(QObject *parent = 0);

public slots:
    virtual void sayHello(int i) =0;
    virtual void sayLightIndex(Trafficlight i) =0;

    virtual void beep() =0;
    virtual void beep(int i) =0;
    virtual void beep(bool b) =0;

    virtual void beepHigh() =0;
    virtual void beepVigilance() =0;
    virtual void beepConfirmation() =0;
    virtual void beepNotification() =0;

    virtual void proccessNewVigilanceRequired (bool required) =0;
    virtual void proccessNewPreAlarmActive (bool active) =0;
    virtual void proccessNewEpvReady (bool ready) =0;
    virtual void proccessVigilanceRequired (bool value) =0;
};

#endif // LEVITHAN_H
