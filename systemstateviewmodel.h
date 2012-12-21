#ifndef SYSTEMSTATEVIEWMODEL_H
#define SYSTEMSTATEVIEWMODEL_H

#include <QDeclarativeItem>

class SystemStateViewModel : public QDeclarativeItem
{
    Q_OBJECT

    // private properties start
    double speedValue;
    Q_PROPERTY(double Speed READ getSpeed WRITE setSpeed NOTIFY SpeedChanged)

    double speedRestrictionValue;
    Q_PROPERTY(double SpeedRestriction READ getSpeedRestriction WRITE setSpeedRestriction NOTIFY SpeedRestrictionChanged)

    double longitudeValue;
    Q_PROPERTY(double Longitude READ getLongitude WRITE setLongitude NOTIFY LongitudeChanged)

    double latitudeValue;
    Q_PROPERTY(double Latitude READ getLatitude WRITE setLatitude NOTIFY LatitudeChanged)

    bool vigilanceRequiredValue;
    Q_PROPERTY(bool IsVigilanceRequired READ getIsVigilanceRequired WRITE setIsVigilanceRequired NOTIFY IsVigilanceRequiredChanged)

    int systemWarningLevelValue;
    Q_PROPERTY(int SystemWarningLevel READ getSystemWarningLevel WRITE setSystemWarningLevel NOTIFY SystemWarningLevelChanged)

    int fullSetWarningLevelValue;
    Q_PROPERTY(int FullSetWarningLevel READ getFullSetWarningLevel WRITE setFullSetWarningLevel NOTIFY FullSetWarningLevelChanged)

    bool pressureOkValue;
    Q_PROPERTY(bool IsPressureOk READ getIsPressureOk WRITE setIsPressureOk NOTIFY IsPressureOkChanged)

    bool epvReadyValue;
    Q_PROPERTY(bool IsEpvReady READ getIsEpvReady WRITE setIsEpvReady NOTIFY IsEpvReadyChanged)

    bool epvReleasedValue;
    Q_PROPERTY(bool IsEpvReleased READ getIsEpvReleased WRITE setIsEpvReleased NOTIFY IsEpvReleasedChanged)

    bool propertyView;
    Q_PROPERTY(bool PropertyView READ getPropertyView WRITE setPropertyView NOTIFY PropertyViewChanged)

    int light;
    Q_PROPERTY(int Light READ getLight WRITE setLight NOTIFY LightChanged)

    QString time;
    Q_PROPERTY(QString Time READ getTime WRITE setTime NOTIFY TimeChanged)

    QString date;
    Q_PROPERTY(QString Date READ getDate WRITE setDate NOTIFY DateChanged)

    int milage;
    Q_PROPERTY(int Milage READ getMilage WRITE setMilage NOTIFY MilageChanged)

    int alsnFreq;
    Q_PROPERTY(int alsnFreq READ getAlsnFreq WRITE setAlsnFreq NOTIFY AlsnFreqChanged)

    // private properties end

public:
    explicit SystemStateViewModel(QDeclarativeItem *parent = 0);

    // public properties start
    const double getSpeed() const;
    void setSpeed(const double);

    const double getSpeedRestriction() const;
    void setSpeedRestriction(const double);

    const double getLongitude() const;
    void setLongitude(const double);

    const double getLatitude() const;
    void setLatitude(const double);

    const bool getIsVigilanceRequired() const;
    void setIsVigilanceRequired(const bool);

    const int getSystemWarningLevel() const;
    void setSystemWarningLevel(const int);

    const int getFullSetWarningLevel() const;
    void setFullSetWarningLevel(const int);

    const bool getIsPressureOk() const;
    void setIsPressureOk(const bool);

    const bool getIsEpvReady() const;
    void setIsEpvReady(const bool);

    const bool getIsEpvReleased() const;
    void setIsEpvReleased(const bool);

    const bool getPropertyView() const;
    void setPropertyView(const bool);

    const int getLight() const;
    void setLight(const int);

    const QString getTime() const;
    void setTime(const QString);

    const QString getDate() const;
    void setDate(const QString);

    const int getMilage() const;
    void setMilage(const int);

    const int getAlsnFreq() const;
    void setAlsnFreq(const int);

    // public properties end

signals:
    // properties signals start
    void SpeedChanged();
    void SpeedRestrictionChanged();
    void LongitudeChanged();
    void LatitudeChanged();
    void IsVigilanceRequiredChanged();
    void SystemWarningLevelChanged();
    void FullSetWarningLevelChanged();
    void IsPressureOkChanged();
    void IsEpvReadyChanged();
    void IsEpvReleasedChanged();
    void PropertyViewChanged();
    void LightChanged();
    void TimeChanged();
    void DateChanged();
    void MilageChanged();
    void AlsnFreqChanged();
    // properties signals end

public slots:
    
};

#endif // SYSTEMSTATEVIEWMODEL_H
