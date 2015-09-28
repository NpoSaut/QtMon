#include "Max100500.h"

Max100500::Max100500(ISpiDev *spiDev)
    : _spiDev(spiDev)
{
}

// Run, Command, run!
// Run, Motherfucker, run!
void Max100500::runCommand(char reg, char val)
{
    QByteArray arr(2);
    arr[0] = reg & 0x7f;
    arr[1] = val;
    _spiDev->transfer(arr);
}

void Max100500::configure()
{
    char config;
    //----------PIRTEBXS
    config |= 0b00000000;
    runCommand(0x04, config);
}

void Max100500::setIntensity()
{
}
