#ifndef SYSTEMSTATEVIEWMODEL_H
#define SYSTEMSTATEVIEWMODEL_H

#include <QDeclarativeItem>

class SystemStateViewModel : public QDeclarativeItem
{
    Q_OBJECT

    // private properties start
    // Текущая скорость
    double speedValue;
    Q_PROPERTY(double Speed READ getSpeed WRITE setSpeed NOTIFY SpeedChanged)

    // Ограничение скорости
    int speedRestrictionValue;
    Q_PROPERTY(int SpeedRestriction READ getSpeedRestriction WRITE setSpeedRestriction NOTIFY SpeedRestrictionChanged)

    // Целевая скорость
    int targetSpeedValue;
    Q_PROPERTY(int TargetSpeed READ getTargetSpeed WRITE setTargetSpeed NOTIFY TargetSpeedChanged)

    // Ускорение
    double accelerationValue;
    Q_PROPERTY(double Acceleration READ getAcceleration WRITE setAcceleration NOTIFY AccelerationChanged)

    // Давление ТЦ
    QString pressureTCValue;
    Q_PROPERTY(QString PressureTC READ getPressureTC WRITE setPressureTC NOTIFY PressureTCChanged)

    // Давление ТМ
    QString pressureTMValue;
    Q_PROPERTY(QString PressureTM READ getPressureTM WRITE setPressureTM NOTIFY PressureTMChanged)

    double longitudeValue;
    Q_PROPERTY(double Longitude READ getLongitude WRITE setLongitude NOTIFY LongitudeChanged)

    double latitudeValue;
    Q_PROPERTY(double Latitude READ getLatitude WRITE setLatitude NOTIFY LatitudeChanged)

    // Общий уровень предупреждений
    int systemWarningLevelValue;
    Q_PROPERTY(int SystemWarningLevel READ getSystemWarningLevel WRITE setSystemWarningLevel NOTIFY SystemWarningLevelChanged)

    // Укомплектованность конфигурации
    int fullSetWarningLevelValue;
    Q_PROPERTY(int FullSetWarningLevel READ getFullSetWarningLevel WRITE setFullSetWarningLevel NOTIFY FullSetWarningLevelChanged)

    // Давление в норме
    bool isPressureOkValue;
    Q_PROPERTY(bool IsPressureOk READ getIsPressureOk WRITE setIsPressureOk NOTIFY IsPressureOkChanged)

    // Готовность ЭПК
    bool isEpvReadyValue;
    Q_PROPERTY(bool IsEpvReady READ getIsEpvReady WRITE setIsEpvReady NOTIFY IsEpvReadyChanged)

    // Признак срыва ЭПК
    bool isEpvReleasedValue;
    Q_PROPERTY(bool IsEpvReleased READ getIsEpvReleased WRITE setIsEpvReleased NOTIFY IsEpvReleasedChanged)

    // Проиденное расстояние
    int milageValue;
    Q_PROPERTY(int Milage READ getMilage WRITE setMilage NOTIFY MilageChanged)

    // Код сигнала светофора (0 - К, 1 - КЖ, ...)
    int lightValue;
    Q_PROPERTY(int Light READ getLight WRITE setLight NOTIFY LightChanged)

    // Частота АЛСН
    int alsnFreqValue;
    Q_PROPERTY(int AlsnFreq READ getAlsnFreq WRITE setAlsnFreq NOTIFY AlsnFreqChanged)

    // Время
    QString timeValue;
    Q_PROPERTY(QString Time READ getTime WRITE setTime NOTIFY TimeChanged)

    // Дата
    QString dateValue;
    Q_PROPERTY(QString Date READ getDate WRITE setDate NOTIFY DateChanged)

    // Наличие кассеты регистрации
    bool isRegistrationTapeActiveValue;
    Q_PROPERTY(bool IsRegistrationTapeActive READ getIsRegistrationTapeActive WRITE setIsRegistrationTapeActive NOTIFY IsRegistrationTapeActiveChanged)

    // Режим движения (0 = П (поездной), 1 = М (маневровый), 2 = Р, 3 = Д)
    int driveModeValue;
    Q_PROPERTY(int DriveMode READ getDriveMode WRITE setDriveMode NOTIFY DriveModeChanged)

    // Необходимость подтверждения бдительности
    bool isVigilanceRequiredValue;
    Q_PROPERTY(bool IsVigilanceRequired READ getIsVigilanceRequired WRITE setIsVigilanceRequired NOTIFY IsVigilanceRequiredChanged)

    // Режим движения (-1 = назад, 0 = стоим, +1 = вперёд)
    int directionValue;
    Q_PROPERTY(int Direction READ getDirection WRITE setDirection NOTIFY DirectionChanged)

    // Неведомо чудо
    bool propertyViewValue;
    Q_PROPERTY(bool PropertyView READ getPropertyView WRITE setPropertyView NOTIFY PropertyViewChanged)

    // private properties end

public:
    explicit SystemStateViewModel(QDeclarativeItem *parent = 0);

    // public properties getters start
    const double getSpeed() const;
    const int getSpeedRestriction() const;
    const int getTargetSpeed() const;
    const double getAcceleration() const;
    const QString getPressureTC() const;
    const QString getPressureTM() const;
    const double getLongitude() const;
    const double getLatitude() const;
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
    const bool getIsRegistrationTapeActive() const;
    const int getDriveMode() const;
    const bool getIsVigilanceRequired() const;
    const int getDirection() const;
    const bool getPropertyView() const;
    // public properties getters end

signals:
    // properties signals start
    void SpeedChanged();
    void SpeedRestrictionChanged();
    void TargetSpeedChanged();
    void AccelerationChanged();
    void PressureTCChanged();
    void PressureTMChanged();
    void LongitudeChanged();
    void LatitudeChanged();
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
    void IsRegistrationTapeActiveChanged();
    void DriveModeChanged();
    void IsVigilanceRequiredChanged();
    void DirectionChanged();
    void PropertyViewChanged();
    // properties signals end

public slots:
    // public properties setters start
    void setSpeed(const double);
    void setSpeedRestriction(const int);
    void setTargetSpeed(const int);
    void setAcceleration(const double);
    void setPressureTC(const QString);
    void setPressureTM(const QString);
    void setLongitude(const double);
    void setLatitude(const double);
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
    void setIsRegistrationTapeActive(const bool);
    void setDriveMode(const int);
    void setIsVigilanceRequired(const bool);
    void setDirection(const int);
    void setPropertyView(const bool);
    // public properties setters end
    
};

#endif // SYSTEMSTATEVIEWMODEL_H
