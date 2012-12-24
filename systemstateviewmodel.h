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
    double getspeedRestrictionValue;
    Q_PROPERTY(double SpeedRestriction READ getSpeedRestriction WRITE setSpeedRestriction NOTIFY SpeedRestrictionChanged)

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

    // public properties start
    // Текущая скорость
    const double getSpeed() const;
    void setSpeed(const double);

    // Ограничение скорости
    const double getSpeedRestriction() const;
    void setSpeedRestriction(const double);

    const double getLongitude() const;
    void setLongitude(const double);

    const double getLatitude() const;
    void setLatitude(const double);

    // Необходимость подтверждения бдительности
    const bool getIsVigilanceRequired() const;
    void setIsVigilanceRequired(const bool);

    // Общий уровень предупреждений
    const int getSystemWarningLevel() const;
    void setSystemWarningLevel(const int);

    // Укомплектованность конфигурации
    const int getFullSetWarningLevel() const;
    void setFullSetWarningLevel(const int);

    // Давление в норме
    const bool getIsPressureOk() const;
    void setIsPressureOk(const bool);

    // Готовность ЭПК
    const bool getIsEpvReady() const;
    void setIsEpvReady(const bool);

    // Признак срыва ЭПК
    const bool getIsEpvReleased() const;
    void setIsEpvReleased(const bool);

    // Проиденное расстояние
    const int getMilage() const;
    void setMilage(const int);

    // Код сигнала светофора (0 - К, 1 - КЖ, ...)
    const int getLight() const;
    void setLight(const int);

    // Частота АЛСН
    const int getAlsnFreq() const;
    void setAlsnFreq(const int);

    // Время
    const QString getTime() const;
    void setTime(const QString);

    // Дата
    const QString getDate() const;
    void setDate(const QString);

    // Неведомо чудо
    const bool getPropertyView() const;
    void setPropertyView(const bool);

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
    void MilageChanged();
    void LightChanged();
    void AlsnFreqChanged();
    void TimeChanged();
    void DateChanged();
    void PropertyViewChanged();
    // properties signals end

public slots:
    
};

#endif // SYSTEMSTATEVIEWMODEL_H
