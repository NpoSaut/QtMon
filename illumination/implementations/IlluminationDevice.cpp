#include "IlluminationDevice.h"

IlluminationDevice::IlluminationDevice(IIntensityConverter *intensityConverter, IAnalogDevice *output) :
    _intensityConverter(intensityConverter), _output(output)
{ }

void IlluminationDevice::setIlluminationValue(double value)
{
    double convertedValue = _intensityConverter->toRange(value);
    _output->setValue(convertedValue);
}
