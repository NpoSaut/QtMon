#ifndef SYSTEMSTATEVIEWMODEL_H
#define SYSTEMSTATEVIEWMODEL_H

#include <QDeclarativeItem>

class SystemStateViewModel : public QDeclarativeItem
{
    Q_OBJECT

    // private properties start
    // Текущая скорость
    double getspeedValue;
    Q_PROPERTY(double Speed READ getSpeed WRITE setSpeed NOTIFY SpeedChanged)

    // Ограничение скорости
    int getspeedRestrictionValue;
    Q_PROPERTY(int SpeedRestriction READ getSpeedRestriction WRITE setSpeedRestriction NOTIFY SpeedRestrictionChanged)

    double getlongitudeValue;
    Q_PROPERTY(double Longitude READ getLongitude WRITE setLongitude NOTIFY LongitudeChanged)

    double getlatitudeValue;
    Q_PROPERTY(double Latitude READ getLatitude WRITE setLatitude NOTIFY LatitudeChanged)

    // Необходимость подтверждения бдительности
    bool getisVigilanceRequiredValue;
    Q_PROPERTY(bool IsVigilanceRequired READ getIsVigilanceRequired WRITE setIsVigilanceRequired NOTIFY IsVigilanceRequiredChanged)

    // Общий уровень предупреждений
    int getsystemWarningLevelValue;
    Q_PROPERTY(int SystemWarningLevel READ getSystemWarningLevel WRITE setSystemWarningLevel NOTIFY SystemWarningLevelChanged)

    // Укомплектованность конфигурации
    int getfullSetWarningLevelValue;
    Q_PROPERTY(int FullSetWarningLevel READ getFullSetWarningLevel WRITE setFullSetWarningLevel NOTIFY FullSetWarningLevelChanged)

    // Давление в норме
    bool getisPressureOkValue;
    Q_PROPERTY(bool IsPressureOk READ getIsPressureOk WRITE setIsPressureOk NOTIFY IsPressureOkChanged)

    // Готовность ЭПК
    bool getisEpvReadyValue;
    Q_PROPERTY(bool IsEpvReady READ getIsEpvReady WRITE setIsEpvReady NOTIFY IsEpvReadyChanged)

    // Признак срыва ЭПК
    bool getisEpvReleasedValue;
    Q_PROPERTY(bool IsEpvReleased READ getIsEpvReleased WRITE setIsEpvReleased NOTIFY IsEpvReleasedChanged)

    // Проиденное расстояние
    int getmilageValue;
    Q_PROPERTY(int Milage READ getMilage WRITE setMilage NOTIFY MilageChanged)

    // Код сигнала светофора (0 - К, 1 - КЖ, ...)
    int getlightValue;
    Q_PROPERTY(int Light READ getLight WRITE setLight NOTIFY LightChanged)

    // Частота АЛСН
    int getalsnFreqValue;
    Q_PROPERTY(int AlsnFreq READ getAlsnFreq WRITE setAlsnFreq NOTIFY AlsnFreqChanged)

    // Время
    QString gettimeValue;
    Q_PROPERTY(QString Time READ getTime WRITE setTime NOTIFY TimeChanged)

    // Дата
    QString getdateValue;
    Q_PROPERTY(QString Date READ getDate WRITE setDate NOTIFY DateChanged)

    // Неведомо чудо
    bool getpropertyViewValue;
    Q_PROPERTY(bool PropertyView READ getPropertyView WRITE setPropertyView NOTIFY PropertyViewChanged)

    // private properties end

public:
    explicit SystemStateViewModel(QDeclarativeItem *parent = 0);

    // public properties getters start
    const double getSpeed() const;
    const int getSpeedRestriction() const;
    const double getLongitude() const;
    const double getLatitude() const;
    const bool getIsVigilanceRequired() const;
    const int getSystemWarningLevel() const;
    const int getFullSetWarningLevel() const;
    const bool getIsPressureOk() const;
    const bool getIsEpvReady() const;
    const bool getIsEpvReleased() const;
    const int getMilage() const;
    const int getLight() const;
    const int getAlsnFreq() const;
    const QString getTime() const;
    const QString getDate() const;
    const bool getPropertyView() const;
    // public properties getters end

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
    void MilageChanged();
    void LightChanged();
    void AlsnFreqChanged();
    void TimeChanged();
    void DateChanged();
    void PropertyViewChanged();
    // properties signals end

public slots:
    // public properties setters start
    void setSpeed(const double);
    void setSpeedRestriction(const int);
    void setLongitude(const double);
    void setLatitude(const double);
    void setIsVigilanceRequired(const bool);
    void setSystemWarningLevel(const int);
    void setFullSetWarningLevel(const int);
    void setIsPressureOk(const bool);
    void setIsEpvReady(const bool);
    void setIsEpvReleased(const bool);
    void setMilage(const int);
    void setLight(const int);
    void setAlsnFreq(const int);
    void setTime(const QString);
    void setDate(const QString);
    void setPropertyView(const bool);
    // public properties setters end
    
};

#endif // SYSTEMSTATEVIEWMODEL_H
