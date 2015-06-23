#ifndef IILLUMINATIONDEVICE_H
#define IILLUMINATIONDEVICE_H

class IIlluminationDevice
{
public:
    IIlluminationDevice() {}

    virtual void setIlluminationValue(double value) = 0;
};

#endif // IILLUMINATIONDEVICE_H
