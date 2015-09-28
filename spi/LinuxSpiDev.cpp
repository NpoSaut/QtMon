#include "LinuxSpiDev.h"

#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

LinuxSpiDev::LinuxSpiDev(QString deviceName, int speedHz)
    : deviceName (deviceName),
      speed (speedHz)
{

}

QByteArray LinuxSpiDev::transfer(QByteArray txData)
{

}
