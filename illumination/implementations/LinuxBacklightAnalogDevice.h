#ifndef LINUXBACKLIGHTANALOGDEVICE_H
#define LINUXBACKLIGHTANALOGDEVICE_H

#include "../interfaces/IAnalogDevice.h"
#include <fstream>


class LinuxBacklightAnalogDevice : public IAnalogDevice
{
public:
    LinuxBacklightAnalogDevice(int number);

    void setValue(double value);

private:
    std::ofstream brightnessFile;
};

#endif // LINUXBACKLIGHTANALOGDEVICE_H
