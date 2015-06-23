#include "DebugAnalogDevice.h"

#include <QDebug>

DebugAnalogDevice::DebugAnalogDevice(QString name) :
    _name(name)
{
}

void DebugAnalogDevice::setValue(double value)
{
    qDebug() << _name << "illumination set to" << value;
}
