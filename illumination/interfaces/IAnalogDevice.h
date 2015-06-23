#ifndef IANALOGDEVICE_H
#define IANALOGDEVICE_H

class IAnalogDevice
{
public:
    IAnalogDevice() { }
    virtual void setValue(double value) = 0;
};

#endif // IANALOGDEVICE_H
