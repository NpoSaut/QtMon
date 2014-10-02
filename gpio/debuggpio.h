#ifndef DEBUGGPIO_H
#define DEBUGGPIO_H

#include "gpio.h"

class DebugGpio : public Gpio
{
public:
    void setDirection (Direction dir);
    Direction getDirection () const;

    void setValue (bool val);
    bool getValue ();

    static Gpio *produce (unsigned number);
private:
    DebugGpio(unsigned num);
    ~DebugGpio ();

    unsigned number;
    Direction direction;
    bool value;
};

#endif // DEBUGGPIO_H
