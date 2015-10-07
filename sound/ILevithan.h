#ifndef ILEVITHAN_H
#define ILEVITHAN_H

#include <QObject>
#include "qtBlokLib/parsers/trafficlight.h"

namespace Sound {

class ILevithan : public QObject
{
    Q_OBJECT
public:
    explicit ILevithan(QObject *parent = 0);

public slots:
    virtual void sayLightIndex(Trafficlight i) =0;

    virtual void beep() =0;
    virtual void beepLong() =0;
    virtual void beepHigh() =0;
    virtual void beepLowHi() =0;
    virtual void beepNotification() =0;
};

}


#endif // ILEVITHAN_H
