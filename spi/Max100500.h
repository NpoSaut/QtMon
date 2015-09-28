#ifndef MAX100500_H
#define MAX100500_H

#include "ISpiDev.h"

class Max100500
{
public:
    Max100500(ISpiDev *spiDev);

private:
    ISpiDev *_spiDev;

    void runCommand(char reg, char val);

    void configure();
    void setIntensity();
};

#endif // MAX100500_H
