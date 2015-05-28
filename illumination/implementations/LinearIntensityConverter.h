#ifndef LINEARINTENSITYCONVERTER_H
#define LINEARINTENSITYCONVERTER_H

#include "../interfaces/IIntensityConverter.h"

class LinearIntensityConverter : public IIntensityConverter
{
    double _scaleFactor;

public:
    LinearIntensityConverter(double scaleFactor = 1.0) : _scaleFactor(scaleFactor) { }

    double toRange(double intensity) { return intensity * _scaleFactor; }
};

#endif // LINEARINTENSITYCONVERTER_H
