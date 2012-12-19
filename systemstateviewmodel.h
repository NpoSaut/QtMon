#ifndef SYSTEMSTATEVIEWMODEL_H
#define SYSTEMSTATEVIEWMODEL_H

#include <QDeclarativeItem>

class SystemStateViewModel : public QDeclarativeItem
{
    Q_OBJECT

    // private properties start
    double speedValue;
    double speedRestrictionValue;
    Q_PROPERTY(double Speed READ getSpeedValue WRITE setSpeedValue NOTIFY speedChanged)
    Q_PROPERTY(double SpeedRestriction READ getSpeedRestrictionValue WRITE setSpeedRestrictionValue NOTIFY speedRestrictionChanged)

    double longitudeValue;
    double latitudeValue;
    Q_PROPERTY(double Longitude READ getLongitudeValue WRITE setLongitudeValue NOTIFY longitudeChanged)
    Q_PROPERTY(double Latitude READ getLatitudeValue WRITE setLatitudeValue NOTIFY latitudeChanged)

    bool vigilanceRequiredValue;
    Q_PROPERTY(bool IsVigilanceRequired READ getIsVigilanceRequired WRITE setIsVigilanceRequired NOTIFY IsVigilanceRequiredChanged)
    // private properties end

public:
    explicit SystemStateViewModel(QDeclarativeItem *parent = 0);

    // public properties start
    const double getSpeedValue() const;
    void setSpeedValue(const double);
    const double getSpeedRestrictionValue() const;
    void setSpeedRestrictionValue(const double);

    const double getLongitudeValue() const;
    void setLongitudeValue(const double);
    const double getLatitudeValue() const;
    void setLatitudeValue(const double);

    const bool getIsVigilanceRequired() const;
    void setIsVigilanceRequired(const bool);
    // public properties end

signals:
    // properties signals start
    void speedChanged();
    void speedRestrictionChanged();

    void longitudeChanged();
    void latitudeChanged();

    void IsVigilanceRequiredChanged();
    // properties signals end


public slots:
    
};

#endif // SYSTEMSTATEVIEWMODEL_H
