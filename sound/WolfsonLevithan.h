#ifndef WOLFSONLEVITHAN_H
#define WOLFSONLEVITHAN_H

#include "ILevithan.h"

#include "viewmodels/systemstateviewmodel.h"
#include "Speaker.h"
#include "QSoundMouth.h"

#include <QSound>

namespace Sound {

class WolfsonLevithan : public ILevithan
{
    Q_OBJECT
public:
    explicit WolfsonLevithan(Speaker *speaker, QObject *parent = 0);

public slots:
    virtual void sayLightIndex(Trafficlight l);

    virtual void beep();
    virtual void beepHigh();
    virtual void beepLong();
    virtual void beepLowHi();
    virtual void beepNotification();

private:
    Speaker *speaker;
    int prevLightIndex;
};

}

#endif // WOLFSONLEVITHAN_H
