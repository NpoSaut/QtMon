#ifndef ISPIDEV_H
#define ISPIDEV_H

#include "QByteArray"

class ISpiDev
{
public:
    virtual QByteArray transfer (QByteArray txData) = 0; // return rxData
};

#endif // ISPIDEV_H
