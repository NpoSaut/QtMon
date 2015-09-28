#include "LinuxSpiDev.h"

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

LinuxSpiDev::LinuxSpiDev(QString deviceName, unsigned speedHz, quint8 bits)
    : deviceName (deviceName),
      speed (speedHz),
      bits (bits)
{
    fd = open(deviceName.toAscii().data(), O_RDWR);

    quint8 mode;
    ioctl(fd, SPI_IOC_WR_MODE, &mode);
    ioctl(fd, SPI_IOC_RD_MODE, &mode);

    ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);

    ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
}

LinuxSpiDev::~LinuxSpiDev()
{
    close (fd);
}

QByteArray LinuxSpiDev::transfer(QByteArray txData)
{
    QByteArray rxData (txData.size(), 0);

    struct spi_ioc_transfer tr;
    tr.tx_buf = (unsigned long)txData.data();
    tr.rx_buf = (unsigned long)rxData.data();
    tr.len = (quint32)txData.size();
    tr.delay_usecs = 0;
    tr.speed_hz = speed;
    tr.bits_per_word = bits;

    int ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
    if (ret < 1)
        return QByteArray ();
    else
        return rxData;
}
