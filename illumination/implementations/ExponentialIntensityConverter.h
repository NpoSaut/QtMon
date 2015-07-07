#ifndef EXPONENTIALINTENSITYCONVERTER_H
#define EXPONENTIALINTENSITYCONVERTER_H

#include "../interfaces/IIntensityConverter.h"

// Конвертирует функцией вида f(x) = a * b^x + c, проходящей через три точки:
// f(0) = y0, f(0,5) = y05, f(1) = y1
class ExponentialIntensityConverter : public IIntensityConverter
{
public:
    ExponentialIntensityConverter(double y0 = 0, double y05 = 0.2, double y1 = 1);

    double toRange(double intensity);

private:
    double a, b, c;
};

#endif // EXPONENTIALINTENSITYCONVERTER_H
