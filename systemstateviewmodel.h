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

    // Корректность скорости
    bool speedIsValidValue;
    Q_PROPERTY(bool SpeedIsValid READ getSpeedIsValid WRITE setSpeedIsValid NOTIFY SpeedIsValidChanged)

    // Текущая скорость по GPS
    double speedFromSkyValue;
    Q_PROPERTY(double SpeedFromSky READ getSpeedFromSky WRITE setSpeedFromSky NOTIFY SpeedFromSkyChanged)

    // Текущая скорость от колеса
    double speedFromEarthValue;
    Q_PROPERTY(double SpeedFromEarth READ getSpeedFromEarth WRITE setSpeedFromEarth NOTIFY SpeedFromEarthChanged)

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

    // Целевая Частота АЛСН
    int alsnFreqTargetValue;
    Q_PROPERTY(int AlsnFreqTarget READ getAlsnFreqTarget WRITE setAlsnFreqTarget NOTIFY AlsnFreqTargetChanged)

    // Фактическая Частота АЛСН
    int alsnFreqFactValue;
    Q_PROPERTY(int AlsnFreqFact READ getAlsnFreqFact WRITE setAlsnFreqFact NOTIFY AlsnFreqFactChanged)

    // Время
    QString timeValue;
    Q_PROPERTY(QString Time READ getTime WRITE setTime NOTIFY TimeChanged)

    // Дата
    QString dateValue;
    Q_PROPERTY(QString Date READ getDate WRITE setDate NOTIFY DateChanged)

    // Наличие кассеты регистрации
    bool isRegistrationTapeActiveValue;
    Q_PROPERTY(bool IsRegistrationTapeActive READ getIsRegistrationTapeActive WRITE setIsRegistrationTapeActive NOTIFY IsRegistrationTapeActiveChanged)

    // Целевой Режим движения
    int driveModeTargetValue;
    Q_PROPERTY(int DriveModeTarget READ getDriveModeTarget WRITE setDriveModeTarget NOTIFY DriveModeTargetChanged)

    // Фактический Режим движения (0 = П (поездной), 1 = М (маневровый), 2 = Р, 3 = Д)
    int driveModeFactValue;
    Q_PROPERTY(int DriveModeFact READ getDriveModeFact WRITE setDriveModeFact NOTIFY DriveModeFactChanged)

    bool ironWheelsValue;
    Q_PROPERTY(bool IronWheels READ getIronWheels WRITE setIronWheels NOTIFY IronWheelsChanged)

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
    const bool getSpeedIsValid() const;
    const double getSpeedFromSky() const;
    const double getSpeedFromEarth() const;
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
    const int getAlsnFreqTarget() const;
    const int getAlsnFreqFact() const;
    const QString getTime() const;
    const QString getDate() const;
    const bool getIsRegistrationTapeActive() const;
    const int getDriveModeTarget() const;
    const int getDriveModeFact() const;
    const bool getIronWheels() const;
    const bool getIsVigilanceRequired() const;
    const int getDirection() const;
    const bool getPropertyView() const;
    // public properties getters end

signals:
    // Сигнал о нажатии кнопки Смены режима движения
    void ChangeDrivemodeButtonPressed();
    void ChangeDrivemodeButtonReleased();

    // Сигнал о нажатии кнопки Выключения Красного
    void DisableRedButtonPressed();
    void DisableRedButtonReleased();

    // properties signals start
    void SpeedChanged();
    void SpeedIsValidChanged();
    void SpeedFromSkyChanged();
    void SpeedFromEarthChanged();
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
    void AlsnFreqTargetChanged();
    void AlsnFreqFactChanged();
    void TimeChanged();
    void DateChanged();
    void IsRegistrationTapeActiveChanged();
    void DriveModeTargetChanged();
    void DriveModeFactChanged();
    void IronWheelsChanged();
    void IsVigilanceRequiredChanged();
    void DirectionChanged();
    void PropertyViewChanged();
    // properties signals end

public slots:
    // public properties setters start
    void setSpeed(const double);
    void setSpeedIsValid(const bool);
    void setSpeedFromSky(const double);
    void setSpeedFromEarth(const double);
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
    void setAlsnFreqTarget(const int);
    void setAlsnFreqFact(const int);
    void setTime(const QString);
    void setDate(const QString);
    void setIsRegistrationTapeActive(const bool);
    void setDriveModeTarget(const int);
    void setDriveModeFact(const int);
    void setIronWheels(const bool);
    void setIsVigilanceRequired(const bool);
    void setDirection(const int);
    void setPropertyView(const bool);
    // public properties setters end
    
};

#endif // SYSTEMSTATEVIEWMODEL_H
