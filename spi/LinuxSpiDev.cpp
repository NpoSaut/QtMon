#include "LinuxSpiDev.h"

LinuxSpiDev::LinuxSpiDev(QString deviceName, int speedHz)
    : deviceName (deviceName),
      speed (speedHz)
{

}

QByteArray LinuxSpiDev::transfer(QByteArray txData)
{

}
