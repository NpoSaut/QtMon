#ifndef SYSTEMSTATEVIEWMODEL_H
#define SYSTEMSTATEVIEWMODEL_H

#include <QDeclarativeItem>

#include "qtBlokLib/modulesactivity.h"
#include "TrafficLightViewModel.h"

namespace ViewModels
{

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

    // В движении
    bool isInMotionValue;
    Q_PROPERTY(bool IsInMotion READ getIsInMotion WRITE setIsInMotion NOTIFY IsInMotionChanged)

    // Ограничение скорости
    int speedRestrictionValue;
    Q_PROPERTY(int SpeedRestriction READ getSpeedRestriction WRITE setSpeedRestriction NOTIFY SpeedRestrictionChanged)

    // Целевая скорость
    int targetSpeedValue;
    Q_PROPERTY(int TargetSpeed READ getTargetSpeed WRITE setTargetSpeed NOTIFY TargetSpeedChanged)

    // Ускорение
    double accelerationValue;
    Q_PROPERTY(double Acceleration READ getAcceleration WRITE setAcceleration NOTIFY AccelerationChanged)

    // Конструктивная скорость
    int designSpeedValue;
    Q_PROPERTY(int DesignSpeed READ getDesignSpeed WRITE setDesignSpeed NOTIFY DesignSpeedChanged)

    // Давление ТЦ
    QString pressureTCValue;
    Q_PROPERTY(QString PressureTC READ getPressureTC WRITE setPressureTC NOTIFY PressureTCChanged)

    // Давление ТМ
    QString pressureTMValue;
    Q_PROPERTY(QString PressureTM READ getPressureTM WRITE setPressureTM NOTIFY PressureTMChanged)

    // Давление УР
    QString pressureURValue;
    Q_PROPERTY(QString PressureUR READ getPressureUR WRITE setPressureUR NOTIFY PressureURChanged)

    // Коэффициент торможения
    float breakingFactorValue;
    Q_PROPERTY(float BreakingFactor READ getBreakingFactor WRITE setBreakingFactor NOTIFY BreakingFactorChanged)

    double longitudeValue;
    Q_PROPERTY(double Longitude READ getLongitude WRITE setLongitude NOTIFY LongitudeChanged)

    double latitudeValue;
    Q_PROPERTY(double Latitude READ getLatitude WRITE setLatitude NOTIFY LatitudeChanged)

    bool gpsValidValue;
    Q_PROPERTY(bool gpsValid READ getGpsValid WRITE setGpsValid NOTIFY gpsValidChanged)

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

    // Строка с активностью модулей
    QString modulesActivityStringValue;
    Q_PROPERTY(QString ModulesActivityString READ getModulesActivityString WRITE setModulesActivityString NOTIFY ModulesActivityStringChanged)

    // Напоминание о выключенности САУТ
    bool sautIsOutNotifierValue;
    Q_PROPERTY(bool SautIsOutNotifier READ getSautIsOutNotifier WRITE setSautIsOutNotifier NOTIFY SautIsOutNotifierChanged)

    // Разбор тяги
    bool isTractionShutdownValue;
    Q_PROPERTY(bool IsTractionShutdown READ getIsTractionShutdown WRITE setIsTractionShutdown NOTIFY IsTractionShutdownChanged)

    // Боксование
    bool isSlippingValue;
    Q_PROPERTY(bool IsSlipping READ getIsSlipping WRITE setIsSlipping NOTIFY IsSlippingChanged)

    // Проиденное расстояние
    int milageValue;
    Q_PROPERTY(int Milage READ getMilage WRITE setMilage NOTIFY MilageChanged)

    // Целевая Частота АЛСН
    int alsnFreqTargetValue;
    Q_PROPERTY(int AlsnFreqTarget READ getAlsnFreqTarget WRITE setAlsnFreqTarget NOTIFY AlsnFreqTargetChanged)

    // Фактическая Частота АЛСН
    int alsnFreqFactValue;
    Q_PROPERTY(int AlsnFreqFact READ getAlsnFreqFact WRITE setAlsnFreqFact NOTIFY AlsnFreqFactChanged)

    // Целевой тип автоблокировки. 0 - АБ, 1 - ПАБ, 2 - ЗАБ.
    int autolockTypeTargetValue;
    Q_PROPERTY(int AutolockTypeTarget READ getAutolockTypeTarget WRITE setAutolockTypeTarget NOTIFY AutolockTypeTargetChanged)

    // Фактический тип автоблокировки. 0 - АБ, 1 - ПАБ, 2 - ЗАБ.
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

    // Название ближайшей станции
    QString nextStatinNameValue;
    Q_PROPERTY(QString NextStatinName READ getNextStatinName WRITE setNextStatinName NOTIFY NextStatinNameChanged)

    // Тип ближайшей цели
    int nextTargetKindValue;
    Q_PROPERTY(int NextTargetKind READ getNextTargetKind WRITE setNextTargetKind NOTIFY NextTargetKindChanged)

    // Название ближайшей цели
    QString nextTargetNameValue;
    Q_PROPERTY(QString NextTargetName READ getNextTargetName WRITE setNextTargetName NOTIFY NextTargetNameChanged)

    // Расстояние до ближайшей цели
    int nextTargetDistanceValue;
    Q_PROPERTY(int NextTargetDistance READ getNextTargetDistance WRITE setNextTargetDistance NOTIFY NextTargetDistanceChanged)

    // Расстояние до цели САУТ
    int sautTargetDistanceValue;
    Q_PROPERTY(int SautTargetDistance READ getSautTargetDistance WRITE setSautTargetDistance NOTIFY SautTargetDistanceChanged)

    // Текст высокоприоритетного сообщения
    QString notificationTextValue;
    Q_PROPERTY(QString NotificationText READ getNotificationText WRITE setNotificationText NOTIFY NotificationTextChanged)

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

    // Разрешение ручного ввода начальной ординаты. К сожалению, не используется. Смотрим на номер пути.
    bool manualOrdinateEnableValue;
    Q_PROPERTY(bool ManualOrdinateEnable READ getManualOrdinateEnable WRITE setManualOrdinateEnable NOTIFY ManualOrdinateEnableChanged)

    // Начальная ордината в ручном режиме
    int manualOrdinateValue;
    Q_PROPERTY(int ManualOrdinate READ getManualOrdinate WRITE setManualOrdinate NOTIFY ManualOrdinateChanged)

    // Увеличение ординаты в ручном режиме. 1 - вперёд, 0 - назад.
    int manualOrdinateIncreaseDirectionValue;
    Q_PROPERTY(int ManualOrdinateIncreaseDirection READ getManualOrdinateIncreaseDirection WRITE setManualOrdinateIncreaseDirection NOTIFY ManualOrdinateIncreaseDirectionChanged)

    // Скорость на белый при ЗАБ
    int autolockSpeedValue;
    Q_PROPERTY(int AutolockSpeed READ getAutolockSpeed WRITE setAutolockSpeed NOTIFY AutolockSpeedChanged)

    // ТСКБМ подключена
    bool tsvcIsOnlineValue;
    Q_PROPERTY(bool TsvcIsOnline READ getTsvcIsOnline WRITE setTsvcIsOnline NOTIFY TsvcIsOnlineChanged)

    // ТСКБМ: машинист бодр
    bool tsvcIsMachinistCheerfulValue;
    Q_PROPERTY(bool TsvcIsMachinistCheerful READ getTsvcIsMachinistCheerful WRITE setTsvcIsMachinistCheerful NOTIFY TsvcIsMachinistCheerfulChanged)

    // ТСКБМ требует подтверждения бдительности
    bool tsvcIsVigilanceRequiredValue;
    Q_PROPERTY(bool TsvcIsVigilanceRequired READ getTsvcIsVigilanceRequired WRITE setTsvcIsVigilanceRequired NOTIFY TsvcIsVigilanceRequiredChanged)

    // Предварительная сигнализация ТСКБМ активна
    bool tsvcIsPreAlarmActiveValue;
    Q_PROPERTY(bool TsvcIsPreAlarmActive READ getTsvcIsPreAlarmActive WRITE setTsvcIsPreAlarmActive NOTIFY TsvcIsPreAlarmActiveChanged)

    // private properties end

    // Активность модулей
    ModulesActivity modulesActivityObjectValue;
    Q_PROPERTY(ModulesActivity ModulesActivityObject READ getModulesActivityObject WRITE setModulesActivityObject NOTIFY ModulesActivityObjectChanged)

    TrafficLightViewModel m_trafficLights;
    Q_PROPERTY(TrafficLightViewModel* trafficLights READ trafficLights NOTIFY trafficLightsChanged)

private slots:
    void convertModulesActivityObjectToString (ModulesActivity ma);
    void checkSautIsOut (ModulesActivity ma);

public:
    explicit SystemStateViewModel(QDeclarativeItem *parent = 0);

    // public properties getters start
    double getSpeed() const;
    bool getSpeedIsValid() const;
    bool getIsInMotion() const;
    int getSpeedRestriction() const;
    int getTargetSpeed() const;
    double getAcceleration() const;
    int getDesignSpeed() const;
    QString getPressureTC() const;
    QString getPressureTM() const;
    QString getPressureUR() const;
    float getBreakingFactor() const;
    double getLongitude() const;
    double getLatitude() const;
    bool getGpsValid() const;
    int getSystemWarningLevel() const;
    int getFullSetWarningLevel() const;
    bool getIsPressureOk() const;
    bool getIsEpvReady() const;
    bool getIsEpvReleased() const;
    QString getModulesActivityString() const;
    bool getSautIsOutNotifier() const;
    bool getIsTractionShutdown() const;
    bool getIsSlipping() const;
    int getMilage() const;
    int getAlsnFreqTarget() const;
    int getAlsnFreqFact() const;
    int getAutolockTypeTarget() const;
    int getAutolockTypeFact() const;
    QString getTime() const;
    QString getDate() const;
    bool getIsRegistrationTapeActive() const;
    int getDriveModeTarget() const;
    int getDriveModeFact() const;
    bool getIronWheels() const;
    bool getIsVigilanceRequired() const;
    bool getIsTractionOn() const;
    int getDirection() const;
    int getOrdinate() const;
    QString getNextStatinName() const;
    int getNextTargetKind() const;
    QString getNextTargetName() const;
    int getNextTargetDistance() const;
    int getSautTargetDistance() const;
    QString getNotificationText() const;
    int getTrackNumber() const;
    int getMachinistNumber() const;
    int getTrainNumber() const;
    int getWagonCount() const;
    int getAxlesCount() const;
    int getTrainMass() const;
    bool getManualOrdinateEnable() const;
    int getManualOrdinate() const;
    int getManualOrdinateIncreaseDirection() const;
    int getAutolockSpeed() const;
    bool getTsvcIsOnline() const;
    bool getTsvcIsMachinistCheerful() const;
    bool getTsvcIsVigilanceRequired() const;
    bool getTsvcIsPreAlarmActive() const;
    // public properties getters end

    ModulesActivity getModulesActivityObject() const;
    TrafficLightViewModel *trafficLights() { return &m_trafficLights; }

signals:
    // Для привязки звуков
    void ButtonPressed();
    void ConfirmButtonPressed();
    void SpeedWarningFlash();
    void WarningLedFlash();

    // Сигнал о нажатии кнопки Смены режима движения
    void ChangeDrivemodeButtonPressed();
    void ChangeDrivemodeButtonReleased();

    // Сигнал о нажатии кнопки Выключения Красного
    void DisableRedButtonPressed();
    void DisableRedButtonReleased();

    // properties signals start
    void SpeedChanged(const double value);
    void SpeedIsValidChanged(const bool value);
    void IsInMotionChanged(const bool value);
    void SpeedRestrictionChanged(const int value);
    void TargetSpeedChanged(const int value);
    void AccelerationChanged(const double value);
    void DesignSpeedChanged(const int value);
    void PressureTCChanged(const QString value);
    void PressureTMChanged(const QString value);
    void PressureURChanged(const QString value);
    void BreakingFactorChanged(const float value);
    void LongitudeChanged(const double value);
    void LatitudeChanged(const double value);
    void gpsValidChanged(const bool value);
    void SystemWarningLevelChanged(const int value);
    void FullSetWarningLevelChanged(const int value);
    void IsPressureOkChanged(const bool value);
    void IsEpvReadyChanged(const bool value);
    void IsEpvReleasedChanged(const bool value);
    void ModulesActivityStringChanged(const QString value);
    void SautIsOutNotifierChanged(const bool value);
    void IsTractionShutdownChanged(const bool value);
    void IsSlippingChanged(const bool value);
    void MilageChanged(const int value);
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
    void NextStatinNameChanged(const QString value);
    void NextTargetKindChanged(const int value);
    void NextTargetNameChanged(const QString value);
    void NextTargetDistanceChanged(const int value);
    void SautTargetDistanceChanged(const int value);
    void NotificationTextChanged(const QString value);
    void TrackNumberChanged(const int value);
    void MachinistNumberChanged(const int value);
    void TrainNumberChanged(const int value);
    void WagonCountChanged(const int value);
    void AxlesCountChanged(const int value);
    void TrainMassChanged(const int value);
    void ManualOrdinateEnableChanged(const bool value);
    void ManualOrdinateChanged(const int value);
    void ManualOrdinateIncreaseDirectionChanged(const int value);
    void AutolockSpeedChanged(const int value);
    void TsvcIsOnlineChanged(const bool value);
    void TsvcIsMachinistCheerfulChanged(const bool value);
    void TsvcIsVigilanceRequiredChanged(const bool value);
    void TsvcIsPreAlarmActiveChanged(const bool value);
    // properties signals end

    void ModulesActivityObjectChanged(const ModulesActivity value);
    void trafficLightsChanged(TrafficLightViewModel* arg);

public slots:
    void setDesignSpeed(int value, bool valid);

    // public properties setters start
    void setSpeed(const double);
    void setSpeedIsValid(const bool);
    void setIsInMotion(const bool);
    void setSpeedRestriction(const int);
    void setTargetSpeed(const int);
    void setAcceleration(const double);
    void setDesignSpeed(const int);
    void setPressureTC(const QString);
    void setPressureTM(const QString);
    void setPressureUR(const QString);
    void setBreakingFactor(const float);
    void setLongitude(const double);
    void setLatitude(const double);
    void setGpsValid(const bool);
    void setSystemWarningLevel(const int);
    void setFullSetWarningLevel(const int);
    void setIsPressureOk(const bool);
    void setIsEpvReady(const bool);
    void setIsEpvReleased(const bool);
    void setModulesActivityString(const QString);
    void setSautIsOutNotifier(const bool);
    void setIsTractionShutdown(const bool);
    void setIsSlipping(const bool);
    void setMilage(const int);
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
    void setNextStatinName(const QString);
    void setNextTargetKind(const int);
    void setNextTargetName(const QString);
    void setNextTargetDistance(const int);
    void setSautTargetDistance(const int);
    void setNotificationText(const QString);
    void setTrackNumber(const int);
    void setMachinistNumber(const int);
    void setTrainNumber(const int);
    void setWagonCount(const int);
    void setAxlesCount(const int);
    void setTrainMass(const int);
    void setManualOrdinateEnable(const bool);
    void setManualOrdinate(const int);
    void setManualOrdinateIncreaseDirection(const int);
    void setAutolockSpeed(const int);
    void setTsvcIsOnline(const bool);
    void setTsvcIsMachinistCheerful(const bool);
    void setTsvcIsVigilanceRequired(const bool);
    void setTsvcIsPreAlarmActive(const bool);
    // public properties setters end
    
    void setModulesActivityObject(const ModulesActivity ma);
};

}

#endif // SYSTEMSTATEVIEWMODEL_H
