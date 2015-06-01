#ifndef EDISSON_H
#define EDISSON_H

#include "interfaces/IIlluminationManager.h"
#include "interfaces/IIlluminationDevice.h"
#include "interfaces/IIlluminationSettings.h"

class Edisson : public IIlluminationManager
{
    double _currentIllumination;
    IIlluminationDevice *_illuminationDevice;
    IIlluminationSettings *_settings;

public:
    Edisson(IIlluminationDevice *illuminationDevice, IIlluminationSettings *settings);

    double illumination();
    void setIllumination(double value);

private:

};

#endif // EDISSON_H
