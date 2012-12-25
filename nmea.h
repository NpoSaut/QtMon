#ifndef NMEA_H
#define NMEA_H

#include <QString>
#include "systemstateviewmodel.h"

class Nmea
{
public:
    Nmea(SystemStateViewModel& viewModel);
    void getNmeaPacket (QString message);

private:
    SystemStateViewModel& viewModel;
    enum Result
    {
        SUCCESS = 1
    };

    Result decodeRMC (QString message);
};

#endif // NMEA_H
