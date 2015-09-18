#ifndef CANLEVITHAN_H
#define CANLEVITHAN_H

#include "Levithan.h"
#include "qtCanLib/ICan.h"

class CanLevithan : public Levithan
{
    Q_OBJECT
public:
    explicit CanLevithan(ICan *can, QObject *parent = 0);

public slots:
    void sayHello(int i) { }
    void sayLightIndex(Trafficlight i) { }

    void beep() { }
    void beep(int i) { }
    void beep(bool b) { }

    void beepHigh();
    void beepVigilance() { }
    void beepConfirmation() { }
    void beepNotification() { }

    void proccessNewVigilanceRequired (bool required) { }
    void proccessNewPreAlarmActive (bool active) { }
    void proccessNewEpvReady (bool ready) { }
    void proccessVigilanceRequired (bool value) { }

private:
    ICan *can;
};

#endif // CANLEVITHAN_H
