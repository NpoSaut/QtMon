#ifndef LINUXSPIDEV_H
#define LINUXSPIDEV_H

#include "QString"

#include "SpiDev.h"

class LinuxSpiDev : public SpiDev
{
public:
    LinuxSpiDev(QString deviceName, int speedHz);
    virtual QByteArray transfer (QByteArray txData); // return rxData

private:
    QString deviceName;
    int speed;
};

#endif // LINUXSPIDEV_H
