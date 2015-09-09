#ifndef LEVITHAN_H
#define LEVITHAN_H

#include <QObject>
#include <QSound>

#include "viewmodels/systemstateviewmodel.h"

#include "sound/speakingthread.h"

class Levithan : public QObject
{
    Q_OBJECT

private:
    sound::Speaker speaker;

public:
    explicit Levithan(QObject *parent = 0);
    
signals:
    
public slots:
    void sayHello(int i);
    void sayLightIndex(int i);

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

#endif // LEVITHAN_H
