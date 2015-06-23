#ifndef IINTENSITYCONVERTER_H
#define IINTENSITYCONVERTER_H

class IIntensityConverter
{
public:
    IIntensityConverter() { }
    virtual double toRange(double intensity) = 0;
};

#endif // IINTENSITYCONVERTER_H
