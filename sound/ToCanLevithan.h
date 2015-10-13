#ifndef ToCANLEVITHAN_H
#define ToCANLEVITHAN_H

#include "ILevithan.h"
#include "qtCanLib/ICan.h"

namespace Sound {

class ToCanLevithan : public ILevithan
{
    Q_OBJECT
public:
    explicit ToCanLevithan(ICan *can, QObject *parent = 0);

public slots:
    virtual void sayLightIndex(Trafficlight i) { /*UNSUPPORTED*/ }

    virtual void beep();
    virtual void beepLong() {beep();}
    virtual void beepHigh() {beep();}
    virtual void beepLowHi() {beep();}
    virtual void beepNotification() {beep();}

private:
    ICan *can;
};

}


#endif // ToCANLEVITHAN_H
