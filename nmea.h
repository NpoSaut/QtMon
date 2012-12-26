#ifndef NMEA_H
#define NMEA_H

#include <QObject>
#include <QString>

class Nmea : public QObject
{
    Q_OBJECT

public:
//    Nmea (QObject* parent);

public slots:
    void getNmeaPacket (QString message);

private:
    enum Result
    {
        SUCCESS = 1
    };

    Result decodeRMC (QString message);

signals:
    void LattitudeChanged (const double lat);
    void LongitudeChanged (const double lon);
    void DateChanged (const QString date);
    void TimeChanged (const QString time);
};

#endif // NMEA_H
