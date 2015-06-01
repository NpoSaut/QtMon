#include "LinuxBacklightAnalogDevice.h"

LinuxBacklightAnalogDevice::LinuxBacklightAnalogDevice(int number)
    : brightnessFile (std::string("/sys/class/backlight/pwm-backlight.") + std::to_string(number) + "/brightness")
{ }

void LinuxBacklightAnalogDevice::setValue(double value)
{
    brightnessFile << int (value);
}
