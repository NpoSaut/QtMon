#ifndef CANBILLCDILLUMINATIONANALOGDEVICE_H
#define CANBILLCDILLUMINATIONANALOGDEVICE_H

#include "illumination/interfaces/IAnalogDevice.h"
#include "qtCanLib/can.h"
#include "qtBlokLib/parsers/BilLcd.h"

class CanBilLcdIlluminationAnalogDevice : public IAnalogDevice
{
public:
    CanBilLcdIlluminationAnalogDevice(Can *can, int cabine);

    void setValue(double value);

private:
    Can *can;
    BilLcd message;
};

#endif // CANBILLCDILLUMINATIONANALOGDEVICE_H
