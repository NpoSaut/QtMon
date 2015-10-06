#ifndef MAX100500_H
#define MAX100500_H

#include "ISpiDev.h"

class Max100500
{
public:
    Max100500(ISpiDev *spiDev);

    void init();
    void setGlobalIntensity(char value);
    void setDigit(int index, char value);
    void setNumber(int value);
    void clear();

private:
    ISpiDev *_spiDev;

    void runCommand(char reg, char val);

    void configure();
};

#endif // MAX100500_H
