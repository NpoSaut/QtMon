#ifndef DEBUGANALOGDEVICE_H
#define DEBUGANALOGDEVICE_H

#include "../interfaces/IAnalogDevice.h"

#include <QString>

class DebugAnalogDevice : public IAnalogDevice
{
    QString _name;

public:
    DebugAnalogDevice(QString name);

    void setValue(double value);
};

#endif // DEBUGANALOGDEVICE_H
