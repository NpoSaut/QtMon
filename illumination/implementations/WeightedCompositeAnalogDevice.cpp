#include "WeightedCompositeAnalogDevice.h"

WeightedCompositeAnalogDevice::WeightedCompositeAnalogDevice(QVector<WeightedAnalogDeviceLeaf *> children) :
    _children(children)
{
}

void WeightedCompositeAnalogDevice::setValue(double value)
{
    foreach (WeightedAnalogDeviceLeaf *child, _children)
    {
        child->device()->setValue(child->weight() * value);
    }
}
