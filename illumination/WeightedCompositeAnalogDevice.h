#ifndef WEIGHTEDCOMPOSITEANALOGDEVICE_H
#define WEIGHTEDCOMPOSITEANALOGDEVICE_H

#include "IAnalogDevice.h"
#include <QVector>

class WeightedCompositeAnalogDevice : IAnalogDevice
{
    class WeightedAnalogDeviceLeaf
    {
        double _weight;
        IAnalogDevice *_device;
    public:
        WeightedAnalogDeviceLeaf(double weight, IAnalogDevice *device) :
            _weight(weight), _device(device)
        { }
        double weight() const { return _weight; }
        IAnalogDevice *device() const { return _device; }
    };

    QVector<WeightedAnalogDeviceLeaf*> _children;

public:
    WeightedCompositeAnalogDevice(QVector<WeightedAnalogDeviceLeaf*> children);

    virtual void setValue(double value);
};

#endif // WEIGHTEDCOMPOSITEANALOGDEVICE_H
