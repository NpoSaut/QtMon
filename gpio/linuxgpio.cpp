#include "linuxgpio.h"

#include <fstream>
#include <iostream>
using namespace std;

class File : public fstream
{
public:
    File (unsigned number, string op)
        : fstream (string("/sys/class/gpio/gpio") + to_string(number) + "/" + op)
    {
        if (!is_open())
            cerr << "GPIO: OPERATION FAILED: Error open file: \""
                 << string("/sys/class/gpio/gpio") + to_string(number) + "/" + op
                 << "\"." << endl;
    }
};

void LinuxGpio::setDirection(Gpio::Direction dir)
{
    File file (number, "direction");
    if ( file.is_open() )
    {
        switch (dir) {
        case Gpio::IN:
            file << "in";
            break;
        case Gpio::OUT:
            file << "out";
            break;
        default:
            cerr << "GPIO: OPERATION FAILED: Unable to set direction of GPIO"<< number <<" ." << " Direction undefined." << endl;
            break;
        }
    }
}

Gpio::Direction LinuxGpio::getDirection() const
{
    File file (number, "direction");
    if ( file.is_open() )
    {
        string dir;
        file >> dir;
        if (dir == "in") {
            return Gpio::IN;
        }
        else if (dir == "out") {
            return Gpio::OUT;
        }
    }
    return Gpio::UNDEF;
}

void LinuxGpio::setValue(bool val)
{
    File file (number, "value");
    if ( file.is_open() )
    {
        file << (val ? "1" : "0");
    }
}

bool LinuxGpio::getValue()
{
    File file (number, "value");
    if ( file.is_open() )
    {
        string val;
        file >> val;
        if (val == "1")
            return true;
        else if (val == "0")
            return false;
        else
            cerr << "GPIO: OPERATION FAILED: Unable to recognize value \"" << val << "\" of GPIO" << number << "." << endl;
    }
    return false;
}

LinuxGpio::LinuxGpio(unsigned num)
    : number (num)
{
    File file (number, "export");
    if ( file.is_open() )
    {
        file << number;
    }
}

LinuxGpio::~LinuxGpio()
{
    File file (number, "unexport");
    if ( file.is_open() )
    {
        file << number;
    }
}

Gpio *LinuxGpio::produce(unsigned number)
{
    return new LinuxGpio (number);
}
