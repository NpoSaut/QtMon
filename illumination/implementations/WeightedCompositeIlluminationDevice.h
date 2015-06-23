#ifndef WEIGHTEDCOMPOSITEILLUMINATIONDEVICE_H
#define WEIGHTEDCOMPOSITEILLUMINATIONDEVICE_H

#include "../interfaces/IIlluminationDevice.h"

#include <QVector>

class WeightedCompositeIlluminationDevice : public IIlluminationDevice
{
public:
    class Leaf
    {
        double _weight;
        IIlluminationDevice *_device;
    public:
        Leaf(double weight, IIlluminationDevice *device) :
            _weight(weight), _device(device)
        { }
        double weight() const { return _weight; }
        IIlluminationDevice *device() const { return _device; }
    };

private:

    QVector<Leaf*> _children;

public:
    WeightedCompositeIlluminationDevice(QVector<Leaf*> children);

    void setIlluminationValue(double value);

};

#endif // WEIGHTEDCOMPOSITEILLUMINATIONDEVICE_H
