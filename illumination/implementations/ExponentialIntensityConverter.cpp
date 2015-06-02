#include "ExponentialIntensityConverter.h"
#include "math.h"

ExponentialIntensityConverter::ExponentialIntensityConverter(double scaleFactor)
    : _scale (scaleFactor)
{ }

double ExponentialIntensityConverter::toRange(double intensity)
{
    return _scale * (pow(2, intensity) - 1);
}
