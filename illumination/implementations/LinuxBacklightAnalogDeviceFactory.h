#ifndef LINUXBACKLIGHTANALOGDEVICEFACTORY_H
#define LINUXBACKLIGHTANALOGDEVICEFACTORY_H

#include "../interfaces/IAnalogDevice.h"

class LinuxBacklightAnalogDeviceFactory
{
public:
    LinuxBacklightAnalogDeviceFactory();

    IAnalogDevice *produce (int backlightNumber);
};

#endif // LINUXBACKLIGHTANALOGDEVICEFACTORY_H
