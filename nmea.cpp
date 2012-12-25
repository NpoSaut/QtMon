#include "nmea.h"
#include "systemstateviewmodel.h"
#include <QStringList>

Nmea::Nmea(SystemStateViewModel& viewModel)
    :viewModel (viewModel)
{
}

void Nmea::getNmeaPacket (QString packet)
{
    if (packet.mid(3,3) == "RMC")
    {
        decodeRMC(packet);
    }
}

Nmea::Result Nmea::decodeRMC(QString message)
{
    QStringList fields = message.split(",");

    // Datetime
    int dth = fields.at(1).mid(0,2).toInt();
    int dtm = fields.at(1).mid(2,2).toInt();
    int dts = fields.at(1).mid(4,2).toInt();
    int dtss = fields.at(1).mid(7,-1).toInt();
    int dtd = fields.at(9).mid(0,2).toInt();
    int dtmn = fields.at(9).mid(2,2).toInt();
    int dty = ("20" + fields.at(9).mid(4,2)).toInt();

    // Reliability
    bool IsReliable = false;
    if (fields.at(2) == "A")
        IsReliable = true;
    else if (fields.at(2) == "V")
        IsReliable = false;

    // Lattitude, degrees
    double latd = fields.at(3).mid(0,2).toDouble();
    double latmmm = fields.at(3).mid(2,-1).toDouble();
    double lat = latd + (1/60)*latmmm;
    if (fields.at(4) == "S")
        lat = -lat;

    // Longitude, degrees
    double lond = fields.at(5).mid(0,3).toDouble();
    double lonmmm = fields.at(5).mid(3,-1).toDouble();
    double lon = latd + (1/60)*latmmm;
    if (fields.at(6) == "W")
        lon = -lon;

    // Push data to viewModel
    if (IsReliable)
    {
        QString time = QString("%1:%2:%3").arg(dth, 2, '0').arg(dtm, 2, '0').arg(dts, 2, '0');
        viewModel.setTime(time);

        QString date = QString("%1/%2/%3").arg(dtd, 2, '0').arg(dtmn, 2, '0').arg(dty, 2, '0');
        viewModel.setTime(date);

        viewModel.setLatitude(lat);
        viewModel.setLongitude(lon);
    }
    return SUCCESS;
}
