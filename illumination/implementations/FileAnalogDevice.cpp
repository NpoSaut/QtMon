#include "FileAnalogDevice.h"

FileAnalogDevice::FileAnalogDevice(std::string fileName)
    : brightnessFile (fileName)
{ }

void FileAnalogDevice::setValue(double value)
{
    brightnessFile << int (value);
    brightnessFile.flush();
}
