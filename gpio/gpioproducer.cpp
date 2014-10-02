#include "gpioproducer.h"

#include "linuxgpio.h"
#include "dummygpio.h"
#include "debuggpio.h"
#include <iostream>

GpioProducer::GpioProducer(GpioType type)
    : type (type)
{ }

Gpio *GpioProducer::produce(unsigned number)
{
    if ( registered.find(number) == registered.end() )
    {
        registered.insert(number);
        return produceRequiredType (number);
    }
    else
    {
        std::cerr << "GPIO: Trying produce (register) alrеady existence GPIO" << number << "." << endl;
        return nullptr;
    }
}

Gpio *GpioProducer::produceRequiredType(unsigned number)
{
    switch (type) {
    case LINUX:
        return LinuxGpio::produce (number);
        break;
    case DUMMY:
        return DummyGpio::produce (number);
        break;
    case DEBUG:
        return DebugGpio::produce (number);
        break;
    default:
        return DummyGpio::produce (number);
        break;
    }
    return DummyGpio::produce (number);
}
