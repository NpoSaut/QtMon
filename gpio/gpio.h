#ifndef GPIO_H
#define GPIO_H

class Gpio
{
public:
    enum Direction
    {
        INPUT = 0,
        OUTPUT = 1,
        UNDEF = 2
    };

    virtual void setDirection (Direction dir) = 0;
    virtual Direction getDirection () const = 0;

    virtual void setValue (bool val) = 0;
    virtual bool getValue () = 0;
};

#endif // GPIO_H
