#ifndef SPIDEV_H
#define SPIDEV_H

#include "QByteArray"

class SpiDev
{
public:
    virtual QByteArray transfer (QByteArray txData) = 0; // return rxData
};

#endif // SPIDEV_H
