#include "CanBilLcdIlluminationAnalogDevice.h"

CanBilLcdIlluminationAnalogDevice::CanBilLcdIlluminationAnalogDevice(Can *can, int cabine)
    : can (can), message (cabine)
{ }

void CanBilLcdIlluminationAnalogDevice::setValue(double value)
{
    message.setLight(value);
    can->transmitMessage(message.encode());
}
