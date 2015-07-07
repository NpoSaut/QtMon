#include "ExponentialIntensityConverter.h"
#include "math.h"

ExponentialIntensityConverter::ExponentialIntensityConverter(double y0, double y05, double y1)
    : a ( pow(y0 - y05, 2) / (y1 - y05 * 2 + y0) ),
      b ( (y1 - y0)/a + 1 ),
      c ( y0 - a )
{ }

double ExponentialIntensityConverter::toRange(double intensity)
{
    return a * pow(b, intensity) + c;
}
