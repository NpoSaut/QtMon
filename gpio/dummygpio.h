#ifndef DUMMYGPIO_H
#define DUMMYGPIO_H

#include "gpio.h"

class DummyGpio : public Gpio
{
public:
    void setDirection (Direction dir) { }
    Direction getDirection () const { return Gpio::UNDEF; }

    void setValue (bool val) { }
    bool getValue () { return false; }

    static Gpio *produce (unsigned number) { return new DummyGpio (); }
private:
    DummyGpio() { }
};

#endif // DUMMYGPIO_H
