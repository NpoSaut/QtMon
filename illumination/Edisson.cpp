#include "Edisson.h"

Edisson::Edisson(IAnalogDevice *outputDevice, IIntensityConverter *intensityConverter, IIlluminationSettings *settings) :
    _currentIllumination(-1), _outputDevice(outputDevice), _intensityConverter(intensityConverter), _settings(settings)
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

    double rangeValue = _intensityConverter->toRange(value);
    _outputDevice->setValue(rangeValue);
}
