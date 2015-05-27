#include "Edisson.h"

Edisson::Edisson(IAnalogDevice *outputDevice, IIntensityConverter *intensityConverter) :
    _outputDevice(outputDevice), _intensityConverter(intensityConverter)
{
}

void Edisson::setIllumination(double value)
{
    double rangeValue = _intensityConverter->toRange(value);
    _outputDevice->setValue(rangeValue);
}
