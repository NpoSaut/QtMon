#include "Max100500.h"

Max100500::Max100500(ISpiDev *spiDev)
    : _spiDev(spiDev)
{ }

void Max100500::init()
{
    configure();
    setGlobalIntensity(0x07);
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
    config |= 0b00000001;
    runCommand(0x04, config);
}

void Max100500::setGlobalIntensity(char value)
{
    runCommand(0x03, value & 0x0F);
}

void Max100500::setDigit(int index, char value)
{
    runCommand(0x10 + index, value & 0x0F);
}

void Max100500::setNumber(int value)
{
    for (int i = 0; i < 2; i++)
    {
        //char digit = (val % (int)pow(10, i + 1)) / (int)pow(10, i);
        //setDigit(i, digit);
        setDigit(i, 6);
    }
}
