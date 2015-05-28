#ifndef EDISSON_H
#define EDISSON_H

#include "interfaces/IAnalogDevice.h"
#include "interfaces/IIntensityConverter.h"
#include "interfaces/IIlluminationSettings.h"

class Edisson
{
    double _currentIllumination;
    IAnalogDevice *_outputDevice;
    IIntensityConverter *_intensityConverter;
    IIlluminationSettings *_settings;

public:
    Edisson(IAnalogDevice *outputDevice, IIntensityConverter *intensityConverter, IIlluminationSettings *settings);

    double Illumination();
    void setIllumination(double value);

private:

};

#endif // EDISSON_H
