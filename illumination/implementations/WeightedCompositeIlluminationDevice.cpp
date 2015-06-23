#include "WeightedCompositeIlluminationDevice.h"

WeightedCompositeIlluminationDevice::WeightedCompositeIlluminationDevice(QVector<WeightedCompositeIlluminationDevice::Leaf *> children) :
    _children(children)
{

}

void WeightedCompositeIlluminationDevice::setIlluminationValue(double value)
{
    foreach (Leaf *child, _children)
    {
        child->device()->setIlluminationValue(child->weight() * value);
    }
}
