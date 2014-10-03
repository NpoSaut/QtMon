#ifndef LINUXGPIO_H
#define LINUXGPIO_H

#include "gpio.h"

class LinuxGpio : public Gpio
{
public:
    void setDirection (Direction dir);
    Direction getDirection () const;

    void setValue (bool val);
    bool getValue ();

    static Gpio *produce (unsigned number);
private:
    LinuxGpio(unsigned num);
    ~LinuxGpio ();

    unsigned number;
};

#endif // LINUXGPIO_H
