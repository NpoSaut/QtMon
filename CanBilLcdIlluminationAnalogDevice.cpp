#include "CanBilLcdIlluminationAnalogDevice.h"

CanBilLcdIlluminationAnalogDevice::CanBilLcdIlluminationAnalogDevice(ICan *can, int cabine)
    : can (can), message (cabine)
{ }

void CanBilLcdIlluminationAnalogDevice::setValue(double value)
{
    message.setLight(value);
    can->send(message.encode());
}
