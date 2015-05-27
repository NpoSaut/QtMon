#ifndef EDISSON_H
#define EDISSON_H

#include "IAnalogDevice.h"
#include "IIntensityConverter.h"

class Edisson
{
    IAnalogDevice *_outputDevice;
    IIntensityConverter *_intensityConverter;

public:
    Edisson(IAnalogDevice *outputDevice, IIntensityConverter *intensityConverter);

    void setIllumination(double value);

private:

};

#endif // EDISSON_H
