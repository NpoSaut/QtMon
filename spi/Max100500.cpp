#include "Max100500.h"
#include "math.h"

Max100500::Max100500(ISpiDev *spiDev)
    : _spiDev(spiDev)
{
    init();
}

void Max100500::init()
{
    configure();
    clear();
    setGlobalIntensity(0x0F);
}

// Run, Command, run!
// Run, Motherfucker, run!
void Max100500::runCommand(char reg, char val)
{
    QByteArray arr(2, 0);
    arr[0] = reg & 0x7f;
    arr[1] = val;
    _spiDev->transfer(arr);
}

void Max100500::configure()
{
    //-----------------PIRTEBXS
    runCommand(0x04, 0b00000001);
    runCommand(0x03, 0x01); // Важно!
}

void Max100500::setGlobalIntensity(char value)
{
    runCommand(0x02, value & 0x0F);
}

void Max100500::setDigit(int index, char value)
{
    runCommand(0x20 + index, 0x30 + value);
}

void Max100500::setNumber(int value)
{
    for (int i = 0; i < 2; i++)
    {
        char digit = (value % (int)pow(10, i + 1)) / (int)pow(10, i);
        setDigit(1 - i, digit);
    }
}

void Max100500::clear()
{
    //-----------------PIRTEBXS
    runCommand(0x04, 0b00100001);
}
