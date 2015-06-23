#ifndef ILLUMINATIONDEVICE_H
#define ILLUMINATIONDEVICE_H

#include "../interfaces/IIntensityConverter.h"
#include "../interfaces/IAnalogDevice.h"

#include "../interfaces/IIlluminationDevice.h"

class IlluminationDevice : public IIlluminationDevice
{
    IIntensityConverter *_intensityConverter;
    IAnalogDevice *_output;

public:
    IlluminationDevice(IIntensityConverter *intensityConverter, IAnalogDevice *output);

    void setIlluminationValue(double value);

};

#endif // ILLUMINATIONDEVICE_H
