#ifndef WOLFSONLEVITHAN_H
#define WOLFSONLEVITHAN_H

#include "Levithan.h"
#include <QSound>

#include "viewmodels/systemstateviewmodel.h"

#include "sound/speakingthread.h"

class WolfsonLevithan : public Levithan
{
    Q_OBJECT

private:
    sound::Speaker speaker;

public:
    explicit WolfsonLevithan(QObject *parent = 0);
    
public slots:
    void sayHello(int i);
    void sayLightIndex(Trafficlight l);

    void beep();
    void beep(int i);
    void beep(bool b);

    void beepHigh();
    void beepVigilance();
    void beepConfirmation();
    void beepNotification();

    void proccessNewVigilanceRequired (bool required);
    void proccessNewPreAlarmActive (bool active);
    void proccessNewEpvReady (bool ready);
    void proccessVigilanceRequired (bool value);

private:
    int prevLightIndex;
};

#endif // WOLFSONLEVITHAN_H