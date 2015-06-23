#ifndef FILEANALOGDEVICE_H
#define FILEANALOGDEVICE_H

#include "../interfaces/IAnalogDevice.h"
#include <fstream>

class FileAnalogDevice : public IAnalogDevice
{
public:
    FileAnalogDevice(std::string fileName);

    void setValue(double value);

private:
    std::ofstream brightnessFile;
};

#endif // FILEANALOGDEVICE_H
