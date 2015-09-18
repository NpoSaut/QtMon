#include "debuggpio.h"

#include <iostream>
using namespace std;

void DebugGpio::setDirection(Gpio::Direction dir)
{
    direction = dir;
    cout << "GPIO: Set direction of GPIO" << number << " to " << int(dir) << "." << endl;
}

Gpio::Direction DebugGpio::getDirection() const
{
    cout << "GPIO: Get direction of GPIO" << number << ": " << int (direction) << "." << endl;
    return direction;
}

void DebugGpio::setValue(bool val)
{
    cout << "GPIO: Set value of GPIO" << number << " to " << val << "." << endl;
    value = val;
}

bool DebugGpio::getValue()
{
    cout << "GPIO: Get value of GPIO" << number << ": " << value << "." << endl;
    return value;
}

DebugGpio::DebugGpio(unsigned num)
    : number (num)
{
    cout << "GPIO: Construct GPIO" << number << "." << endl;
}

DebugGpio::~DebugGpio()
{
    cout << "GPIO: Destroy GPIO" << number << "." << endl;
}

Gpio *DebugGpio::produce(unsigned number)
{
    return new DebugGpio (number);
}
