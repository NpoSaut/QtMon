#ifndef LINUXSPIDEV_H
#define LINUXSPIDEV_H

#include "QString"

#include "ISpiDev.h"

class LinuxSpiDev : public ISpiDev
{
public:
    LinuxSpiDev(QString deviceName, unsigned speedHz, quint8 bits = 8);
    ~LinuxSpiDev();

    virtual QByteArray transfer (QByteArray txData); // return rxData

private:
    QString deviceName;
    quint32 speed;
    quint8 bits;
    int fd;
};

#endif // LINUXSPIDEV_H
