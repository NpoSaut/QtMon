#ifndef EXPONENTIALINTENSITYCONVERTER_H
#define EXPONENTIALINTENSITYCONVERTER_H

#include "../interfaces/IIntensityConverter.h"

class ExponentialIntensityConverter : public IIntensityConverter
{
public:
    ExponentialIntensityConverter(double scaleFactor = 1.0);

    double toRange(double intensity);

private:
    double _scale;
};

#endif // EXPONENTIALINTENSITYCONVERTER_H
