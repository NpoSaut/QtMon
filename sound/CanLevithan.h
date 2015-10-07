#ifndef CANLEVITHAN_H
#define CANLEVITHAN_H

#include "ILevithan.h"
#include "qtCanLib/ICan.h"

namespace Sound {

class CanLevithan : public ILevithan
{
    Q_OBJECT
public:
    explicit CanLevithan(ICan *can, QObject *parent = 0);

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


#endif // CANLEVITHAN_H
