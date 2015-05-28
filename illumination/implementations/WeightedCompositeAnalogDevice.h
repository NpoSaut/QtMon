#ifndef WEIGHTEDCOMPOSITEANALOGDEVICE_H
#define WEIGHTEDCOMPOSITEANALOGDEVICE_H

#include "../interfaces/IAnalogDevice.h"
#include <QVector>

class WeightedCompositeAnalogDevice : public IAnalogDevice
{
public:
    class Leaf
    {
        double _weight;
        IAnalogDevice *_device;
    public:
        Leaf(double weight, IAnalogDevice *device) :
            _weight(weight), _device(device)
        { }
        double weight() const { return _weight; }
        IAnalogDevice *device() const { return _device; }
    };

private:

    QVector<Leaf*> _children;

public:
    WeightedCompositeAnalogDevice(QVector<Leaf*> children);

    virtual void setValue(double value);
};

#endif // WEIGHTEDCOMPOSITEANALOGDEVICE_H
