#include "Edisson.h"

Edisson::Edisson(IIlluminationDevice *illuminationDevice, IIlluminationSettings *settings) :
    _currentIllumination(-1), _illuminationDevice(illuminationDevice), _settings(settings)
{
    double storedIllumination = _settings->getIlluminationValue();
    setIllumination(storedIllumination);
}

double Edisson::illumination()
{
    return _currentIllumination;
}

void Edisson::setIllumination(double value)
{
    if (value == _currentIllumination) return;
    _currentIllumination = value;
    _settings->storeIlluminationValue(value);
    _illuminationDevice->setIlluminationValue(value);
}
