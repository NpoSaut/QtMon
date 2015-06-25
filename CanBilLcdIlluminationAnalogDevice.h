#ifndef CANBILLCDILLUMINATIONANALOGDEVICE_H
#define CANBILLCDILLUMINATIONANALOGDEVICE_H

#include "illumination/interfaces/IAnalogDevice.h"
#include "qtCanLib/ICan.h"
#include "qtBlokLib/parsers/BilLcd.h"

class CanBilLcdIlluminationAnalogDevice : public IAnalogDevice
{
public:
    CanBilLcdIlluminationAnalogDevice(ICan *can, int cabine);

    void setValue(double value);

private:
    ICan *can;
    BilLcd message;
};

#endif // CANBILLCDILLUMINATIONANALOGDEVICE_H
