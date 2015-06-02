#include "LinuxBacklightAnalogDeviceFactory.h"
#include "FileAnalogDevice.h"

LinuxBacklightAnalogDeviceFactory::LinuxBacklightAnalogDeviceFactory()
{ }

IAnalogDevice *LinuxBacklightAnalogDeviceFactory::produce(int backlightNumber)
{
    return new FileAnalogDevice (std::string("/sys/class/backlight/pwm-backlight.") + std::to_string(backlightNumber) + "/brightness");
}
