#ifndef SYSTEMSTATEVIEWMODEL_H
#define SYSTEMSTATEVIEWMODEL_H

#include <QDeclarativeItem>

#include "qtBlokLib/modulesactivity.h"

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

    // Активность модулей
    QString modulesActivityStringValue;
    Q_PROPERTY(QString ModulesActivityString READ getModulesActivityString WRITE setModulesActivityString NOTIFY ModulesActivityStringChanged)

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

    // Целевой тип автоблокировки
    int autolockTypeTargetValue;
    Q_PROPERTY(int AutolockTypeTarget READ getAutolockTypeTarget WRITE setAutolockTypeTarget NOTIFY AutolockTypeTargetChanged)

    // Фактический тип автоблокировки
    int autolockTypeFactValue;
    Q_PROPERTY(int AutolockTypeFact READ getAutolockTypeFact WRITE setAutolockTypeFact NOTIFY AutolockTypeFactChanged)

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
    Q_PROPERTY(int DriveModeTarget READ getDriveModeTarget WRITE setDriveModeTarget NOTIFY driveModeTargetChanged)

    // Фактический Режим движения (0 = П (поездной), 1 = М (маневровый), 2 = Р, 3 = Д)
    int driveModeFactValue;
    Q_PROPERTY(int DriveModeFact READ getDriveModeFact WRITE setDriveModeFact NOTIFY driveModeFactChanged)

    bool ironWheelsValue;
    Q_PROPERTY(bool IronWheels READ getIronWheels WRITE setIronWheels NOTIFY IronWheelsChanged)

    // Необходимость подтверждения бдительности
    bool isVigilanceRequiredValue;
    Q_PROPERTY(bool IsVigilanceRequired READ getIsVigilanceRequired WRITE setIsVigilanceRequired NOTIFY IsVigilanceRequiredChanged)

    // Тяга включена
    bool isTractionOnValue;
    Q_PROPERTY(bool IsTractionOn READ getIsTractionOn WRITE setIsTractionOn NOTIFY IsTractionOnChanged)

    // Режим движения (-1 = назад, 0 = стоим, +1 = вперёд)
    int directionValue;
    Q_PROPERTY(int Direction READ getDirection WRITE setDirection NOTIFY DirectionChanged)

    // Текущая ордината
    int ordinateValue;
    Q_PROPERTY(int Ordinate READ getOrdinate WRITE setOrdinate NOTIFY OrdinateChanged)

    // Тип ближайшей цели
    int nextTargetKindValue;
    Q_PROPERTY(int NextTargetKind READ getNextTargetKind WRITE setNextTargetKind NOTIFY NextTargetKindChanged)

    // Название ближайшей цели
    QString nextTargetNameValue;
    Q_PROPERTY(QString NextTargetName READ getNextTargetName WRITE setNextTargetName NOTIFY NextTargetNameChanged)

    // Расстояние до ближайшей цели
    int nextTargetDistanceValue;
    Q_PROPERTY(int NextTargetDistance READ getNextTargetDistance WRITE setNextTargetDistance NOTIFY NextTargetDistanceChanged)

    // Текст высокоприоритетного сообщения
    QString warningTextValue;
    Q_PROPERTY(QString WarningText READ getWarningText WRITE setWarningText NOTIFY WarningTextChanged)

    // Текст низкоприоритетного сообщения
    QString infoTextValue;
    Q_PROPERTY(QString InfoText READ getInfoText WRITE setInfoText NOTIFY InfoTextChanged)

    // Номер пути
    int trackNumberValue;
    Q_PROPERTY(int TrackNumber READ getTrackNumber WRITE setTrackNumber NOTIFY TrackNumberChanged)

    // Номер машиниста
    int machinistNumberValue;
    Q_PROPERTY(int MachinistNumber READ getMachinistNumber WRITE setMachinistNumber NOTIFY MachinistNumberChanged)

    // Номер поезда
    int trainNumberValue;
    Q_PROPERTY(int TrainNumber READ getTrainNumber WRITE setTrainNumber NOTIFY TrainNumberChanged)

    // Длина поезда в условных вагонах
    int wagonCountValue;
    Q_PROPERTY(int WagonCount READ getWagonCount WRITE setWagonCount NOTIFY WagonCountChanged)

    // Длина поезда в осях
    int axlesCountValue;
    Q_PROPERTY(int AxlesCount READ getAxlesCount WRITE setAxlesCount NOTIFY AxlesCountChanged)

    // Масса поезда
    int trainMassValue;
    Q_PROPERTY(int TrainMass READ getTrainMass WRITE setTrainMass NOTIFY TrainMassChanged)

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
    const QString getModulesActivityString() const;
    const int getMilage() const;
    const int getLight() const;
    const int getAlsnFreqTarget() const;
    const int getAlsnFreqFact() const;
    const int getAutolockTypeTarget() const;
    const int getAutolockTypeFact() const;
    const QString getTime() const;
    const QString getDate() const;
    const bool getIsRegistrationTapeActive() const;
    const int getDriveModeTarget() const;
    const int getDriveModeFact() const;
    const bool getIronWheels() const;
    const bool getIsVigilanceRequired() const;
    const bool getIsTractionOn() const;
    const int getDirection() const;
    const int getOrdinate() const;
    const int getNextTargetKind() const;
    const QString getNextTargetName() const;
    const int getNextTargetDistance() const;
    const QString getWarningText() const;
    const QString getInfoText() const;
    const int getTrackNumber() const;
    const int getMachinistNumber() const;
    const int getTrainNumber() const;
    const int getWagonCount() const;
    const int getAxlesCount() const;
    const int getTrainMass() const;
    // public properties getters end

signals:
    // Для привязки звуков
    void ButtonPressed();
    void ConfirmButtonPressed();
    void SpeedWarningFlash();

    // Сигнал о нажатии кнопки Смены режима движения
    void ChangeDrivemodeButtonPressed();
    void ChangeDrivemodeButtonReleased();

    // Сигнал о нажатии кнопки Выключения Красного
    void DisableRedButtonPressed();
    void DisableRedButtonReleased();

    // properties signals start
    void SpeedChanged(const double value);
    void SpeedIsValidChanged(const bool value);
    void SpeedFromSkyChanged(const double value);
    void SpeedFromEarthChanged(const double value);
    void SpeedRestrictionChanged(const int value);
    void TargetSpeedChanged(const int value);
    void AccelerationChanged(const double value);
    void PressureTCChanged(const QString value);
    void PressureTMChanged(const QString value);
    void LongitudeChanged(const double value);
    void LatitudeChanged(const double value);
    void SystemWarningLevelChanged(const int value);
    void FullSetWarningLevelChanged(const int value);
    void IsPressureOkChanged(const bool value);
    void IsEpvReadyChanged(const bool value);
    void IsEpvReleasedChanged(const bool value);
    void ModulesActivityStringChanged(const QString value);
    void MilageChanged(const int value);
    void LightChanged(const int value);
    void AlsnFreqTargetChanged(const int value);
    void AlsnFreqFactChanged(const int value);
    void AutolockTypeTargetChanged(const int value);
    void AutolockTypeFactChanged(const int value);
    void TimeChanged(const QString value);
    void DateChanged(const QString value);
    void IsRegistrationTapeActiveChanged(const bool value);
    void driveModeTargetChanged(const int value);
    void driveModeFactChanged(const int value);
    void IronWheelsChanged(const bool value);
    void IsVigilanceRequiredChanged(const bool value);
    void IsTractionOnChanged(const bool value);
    void DirectionChanged(const int value);
    void OrdinateChanged(const int value);
    void NextTargetKindChanged(const int value);
    void NextTargetNameChanged(const QString value);
    void NextTargetDistanceChanged(const int value);
    void WarningTextChanged(const QString value);
    void InfoTextChanged(const QString value);
    void TrackNumberChanged(const int value);
    void MachinistNumberChanged(const int value);
    void TrainNumberChanged(const int value);
    void WagonCountChanged(const int value);
    void AxlesCountChanged(const int value);
    void TrainMassChanged(const int value);
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
    void setModulesActivityString(const QString);
    void setMilage(const int);
    void setLight(const int);
    void setAlsnFreqTarget(const int);
    void setAlsnFreqFact(const int);
    void setAutolockTypeTarget(const int);
    void setAutolockTypeFact(const int);
    void setTime(const QString);
    void setDate(const QString);
    void setIsRegistrationTapeActive(const bool);
    void setDriveModeTarget(const int);
    void setDriveModeFact(const int);
    void setIronWheels(const bool);
    void setIsVigilanceRequired(const bool);
    void setIsTractionOn(const bool);
    void setDirection(const int);
    void setOrdinate(const int);
    void setNextTargetKind(const int);
    void setNextTargetName(const QString);
    void setNextTargetDistance(const int);
    void setWarningText(const QString);
    void setInfoText(const QString);
    void setTrackNumber(const int);
    void setMachinistNumber(const int);
    void setTrainNumber(const int);
    void setWagonCount(const int);
    void setAxlesCount(const int);
    void setTrainMass(const int);
    // public properties setters end
    
};

#endif // SYSTEMSTATEVIEWMODEL_H
