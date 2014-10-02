#ifndef GPIOPRODUCER_H
#define GPIOPRODUCER_H

#include <set>

#include "gpio.h"

class GpioProducer
{
public:
    enum GpioType
    {
        LINUX = 0,
        DUMMY = 1,
        DEBUG = 2
    };

    GpioProducer(GpioType type);

    Gpio *produce (unsigned number);

private:
    Gpio *produceRequiredType (unsigned number);

    GpioType type;
    std::set<unsigned> registered;
};

#endif // GPIOPRODUCER_H
