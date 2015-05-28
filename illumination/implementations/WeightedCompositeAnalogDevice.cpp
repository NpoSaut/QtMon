#include "WeightedCompositeAnalogDevice.h"

WeightedCompositeAnalogDevice::WeightedCompositeAnalogDevice(QVector<Leaf *> children) :
    _children(children)
{
}

void WeightedCompositeAnalogDevice::setValue(double value)
{
    foreach (Leaf *child, _children)
    {
        child->device()->setValue(child->weight() * value);
    }
}
