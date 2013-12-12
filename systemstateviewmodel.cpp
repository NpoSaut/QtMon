#include "systemstateviewmodel.h"

SystemStateViewModel::SystemStateViewModel(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    // fileds init start
    speedValue = 0;
    speedIsValidValue = false;
    speedFromSkyValue = -1;
    speedFromEarthValue = 0;
    speedRestrictionValue = 40;
    targetSpeedValue = 55;
    accelerationValue = 0;
    designSpeedValue = 40;
    pressureTCValue = "0.00";
    pressureTMValue = "0.00";
    pressureURValue = "0.00";
    longitudeValue = 60.4688;
    latitudeValue = 56.88397;
    gpsValidValue = false;
    systemWarningLevelValue = 0;
    fullSetWarningLevelValue = 0;
    isPressureOkValue = true;
    isEpvReadyValue = true;
    isEpvReleasedValue = false;
    modulesActivityStringValue = "------------";
    milageValue = 0;
    lightValue = -2;
    alsnFreqTargetValue = -1;
    alsnFreqFactValue = -1;
    autolockTypeTargetValue = -1;
    autolockTypeFactValue = -1;
    timeValue = "-:-";
    dateValue = "- / - / -";
    isRegistrationTapeActiveValue = false;
    driveModeTargetValue = -1;
    driveModeFactValue = -1;
    ironWheelsValue = true;
    isVigilanceRequiredValue = true;
    isTractionOnValue = false;
    directionValue = 0;
    ordinateValue = 1100;
    nextTargetKindValue = -1;
    nextTargetNameValue = "";
    nextTargetDistanceValue = 0;
    notificationTextValue = "";
    trackNumberValue = 0;
    machinistNumberValue = 0;
    trainNumberValue = 0;
    wagonCountValue = 1;
    axlesCountValue = 4;
    trainMassValue = 0;
    manualOrdinateEnableValue = false;
    manualOrdinateValue = 1100;
    manualOrdinateIncreaseDirectionValue = 1;
    autolockSpeedValue = 40;
    tsvcIsOnlineValue = false;
    tsvcIsMachinistCheerfulValue = false;
    tsvcIsVigilanceRequiredValue = false;
    tsvcIsPreAlarmActiveValue = false;
    // fileds init end
}

// -- start: Properties Getters and Setters --
// Текущая скорость
const double SystemStateViewModel::getSpeed() const
{
    return speedValue;
}
void SystemStateViewModel::setSpeed(const double value)
{
    if (speedValue != value)
    {
        speedValue = value;
        emit SpeedChanged(value);
    }
}

// Корректность скорости
const bool SystemStateViewModel::getSpeedIsValid() const
{
    return speedIsValidValue;
}
void SystemStateViewModel::setSpeedIsValid(const bool value)
{
    if (speedIsValidValue != value)
    {
        speedIsValidValue = value;
        emit SpeedIsValidChanged(value);
    }
}

// Текущая скорость по GPS
const double SystemStateViewModel::getSpeedFromSky() const
{
    return speedFromSkyValue;
}
void SystemStateViewModel::setSpeedFromSky(const double value)
{
    if (speedFromSkyValue != value)
    {
        speedFromSkyValue = value;
        emit SpeedFromSkyChanged(value);
    }
}

// Текущая скорость от колеса
const double SystemStateViewModel::getSpeedFromEarth() const
{
    return speedFromEarthValue;
}
void SystemStateViewModel::setSpeedFromEarth(const double value)
{
    if (speedFromEarthValue != value)
    {
        speedFromEarthValue = value;
        emit SpeedFromEarthChanged(value);
    }
}

// Ограничение скорости
const int SystemStateViewModel::getSpeedRestriction() const
{
    return speedRestrictionValue;
}
void SystemStateViewModel::setSpeedRestriction(const int value)
{
    if (speedRestrictionValue != value)
    {
        speedRestrictionValue = value;
        emit SpeedRestrictionChanged(value);
    }
}

// Целевая скорость
const int SystemStateViewModel::getTargetSpeed() const
{
    return targetSpeedValue;
}
void SystemStateViewModel::setTargetSpeed(const int value)
{
    if (targetSpeedValue != value)
    {
        targetSpeedValue = value;
        emit TargetSpeedChanged(value);
    }
}

// Ускорение
const double SystemStateViewModel::getAcceleration() const
{
    return accelerationValue;
}
void SystemStateViewModel::setAcceleration(const double value)
{
    if (accelerationValue != value)
    {
        accelerationValue = value;
        emit AccelerationChanged(value);
    }
}

// Конструктивная скорость
const int SystemStateViewModel::getDesignSpeed() const
{
    return designSpeedValue;
}
void SystemStateViewModel::setDesignSpeed(const int value)
{
    if (designSpeedValue != value)
    {
        designSpeedValue = value;
        emit DesignSpeedChanged(value);
    }
}

// Давление ТЦ
const QString SystemStateViewModel::getPressureTC() const
{
    return pressureTCValue;
}
void SystemStateViewModel::setPressureTC(const QString value)
{
    if (pressureTCValue != value)
    {
        pressureTCValue = value;
        emit PressureTCChanged(value);
    }
}

// Давление ТМ
const QString SystemStateViewModel::getPressureTM() const
{
    return pressureTMValue;
}
void SystemStateViewModel::setPressureTM(const QString value)
{
    if (pressureTMValue != value)
    {
        pressureTMValue = value;
        emit PressureTMChanged(value);
    }
}

// Давление УР
const QString SystemStateViewModel::getPressureUR() const
{
    return pressureURValue;
}
void SystemStateViewModel::setPressureUR(const QString value)
{
    if (pressureURValue != value)
    {
        pressureURValue = value;
        emit PressureURChanged(value);
    }
}

const double SystemStateViewModel::getLongitude() const
{
    return longitudeValue;
}
void SystemStateViewModel::setLongitude(const double value)
{
    if (longitudeValue != value)
    {
        longitudeValue = value;
        emit LongitudeChanged(value);
    }
}

const double SystemStateViewModel::getLatitude() const
{
    return latitudeValue;
}
void SystemStateViewModel::setLatitude(const double value)
{
    if (latitudeValue != value)
    {
        latitudeValue = value;
        emit LatitudeChanged(value);
    }
}

const bool SystemStateViewModel::getGpsValid() const
{
    return gpsValidValue;
}
void SystemStateViewModel::setGpsValid(const bool value)
{
    if (gpsValidValue != value)
    {
        gpsValidValue = value;
        emit gpsValidChanged(value);
    }
}

// Общий уровень предупреждений
const int SystemStateViewModel::getSystemWarningLevel() const
{
    return systemWarningLevelValue;
}
void SystemStateViewModel::setSystemWarningLevel(const int value)
{
    if (systemWarningLevelValue != value)
    {
        systemWarningLevelValue = value;
        emit SystemWarningLevelChanged(value);
    }
}

// Укомплектованность конфигурации
const int SystemStateViewModel::getFullSetWarningLevel() const
{
    return fullSetWarningLevelValue;
}
void SystemStateViewModel::setFullSetWarningLevel(const int value)
{
    if (fullSetWarningLevelValue != value)
    {
        fullSetWarningLevelValue = value;
        emit FullSetWarningLevelChanged(value);
    }
}

// Давление в норме
const bool SystemStateViewModel::getIsPressureOk() const
{
    return isPressureOkValue;
}
void SystemStateViewModel::setIsPressureOk(const bool value)
{
    if (isPressureOkValue != value)
    {
        isPressureOkValue = value;
        emit IsPressureOkChanged(value);
    }
}

// Готовность ЭПК
const bool SystemStateViewModel::getIsEpvReady() const
{
    return isEpvReadyValue;
}
void SystemStateViewModel::setIsEpvReady(const bool value)
{
    if (isEpvReadyValue != value)
    {
        isEpvReadyValue = value;
        emit IsEpvReadyChanged(value);
    }
}

// Признак срыва ЭПК
const bool SystemStateViewModel::getIsEpvReleased() const
{
    return isEpvReleasedValue;
}
void SystemStateViewModel::setIsEpvReleased(const bool value)
{
    if (isEpvReleasedValue != value)
    {
        isEpvReleasedValue = value;
        emit IsEpvReleasedChanged(value);
    }
}

// Активность модулей
const QString SystemStateViewModel::getModulesActivityString() const
{
    return modulesActivityStringValue;
}
void SystemStateViewModel::setModulesActivityString(const QString value)
{
    if (modulesActivityStringValue != value)
    {
        modulesActivityStringValue = value;
        emit ModulesActivityStringChanged(value);
    }
}

// Проиденное расстояние
const int SystemStateViewModel::getMilage() const
{
    return milageValue;
}
void SystemStateViewModel::setMilage(const int value)
{
    if (milageValue != value)
    {
        milageValue = value;
        emit MilageChanged(value);
    }
}

// Код сигнала светофора (0 - К, 1 - КЖ, ...)
const int SystemStateViewModel::getLight() const
{
    return lightValue;
}
void SystemStateViewModel::setLight(const int value)
{
    if (lightValue != value)
    {
        lightValue = value;
        emit LightChanged(value);
    }
}

// Целевая Частота АЛСН
const int SystemStateViewModel::getAlsnFreqTarget() const
{
    return alsnFreqTargetValue;
}
void SystemStateViewModel::setAlsnFreqTarget(const int value)
{
    if (alsnFreqTargetValue != value)
    {
        alsnFreqTargetValue = value;
        emit AlsnFreqTargetChanged(value);
    }
}

// Фактическая Частота АЛСН
const int SystemStateViewModel::getAlsnFreqFact() const
{
    return alsnFreqFactValue;
}
void SystemStateViewModel::setAlsnFreqFact(const int value)
{
    if (alsnFreqFactValue != value)
    {
        alsnFreqFactValue = value;
        emit AlsnFreqFactChanged(value);
    }
}

// Целевой тип автоблокировки. 0 - АБ, 1 - ПАБ, 2 - ЗАБ.
const int SystemStateViewModel::getAutolockTypeTarget() const
{
    return autolockTypeTargetValue;
}
void SystemStateViewModel::setAutolockTypeTarget(const int value)
{
    if (autolockTypeTargetValue != value)
    {
        autolockTypeTargetValue = value;
        emit AutolockTypeTargetChanged(value);
    }
}

// Фактический тип автоблокировки. 0 - АБ, 1 - ПАБ, 2 - ЗАБ.
const int SystemStateViewModel::getAutolockTypeFact() const
{
    return autolockTypeFactValue;
}
void SystemStateViewModel::setAutolockTypeFact(const int value)
{
    if (autolockTypeFactValue != value)
    {
        autolockTypeFactValue = value;
        emit AutolockTypeFactChanged(value);
    }
}

// Время
const QString SystemStateViewModel::getTime() const
{
    return timeValue;
}
void SystemStateViewModel::setTime(const QString value)
{
    if (timeValue != value)
    {
        timeValue = value;
        emit TimeChanged(value);
    }
}

// Дата
const QString SystemStateViewModel::getDate() const
{
    return dateValue;
}
void SystemStateViewModel::setDate(const QString value)
{
    if (dateValue != value)
    {
        dateValue = value;
        emit DateChanged(value);
    }
}

// Наличие кассеты регистрации
const bool SystemStateViewModel::getIsRegistrationTapeActive() const
{
    return isRegistrationTapeActiveValue;
}
void SystemStateViewModel::setIsRegistrationTapeActive(const bool value)
{
    if (isRegistrationTapeActiveValue != value)
    {
        isRegistrationTapeActiveValue = value;
        emit IsRegistrationTapeActiveChanged(value);
    }
}

// Целевой Режим движения
const int SystemStateViewModel::getDriveModeTarget() const
{
    return driveModeTargetValue;
}
void SystemStateViewModel::setDriveModeTarget(const int value)
{
    if (driveModeTargetValue != value)
    {
        driveModeTargetValue = value;
        emit driveModeTargetChanged(value);
    }
}

// Фактический Режим движения (0 = П (поездной), 1 = М (маневровый), 2 = Р, 3 = Д)
const int SystemStateViewModel::getDriveModeFact() const
{
    return driveModeFactValue;
}
void SystemStateViewModel::setDriveModeFact(const int value)
{
    if (driveModeFactValue != value)
    {
        driveModeFactValue = value;
        emit driveModeFactChanged(value);
    }
}

const bool SystemStateViewModel::getIronWheels() const
{
    return ironWheelsValue;
}
void SystemStateViewModel::setIronWheels(const bool value)
{
    if (ironWheelsValue != value)
    {
        ironWheelsValue = value;
        emit IronWheelsChanged(value);
    }
}

// Необходимость подтверждения бдительности
const bool SystemStateViewModel::getIsVigilanceRequired() const
{
    return isVigilanceRequiredValue;
}
void SystemStateViewModel::setIsVigilanceRequired(const bool value)
{
    if (isVigilanceRequiredValue != value)
    {
        isVigilanceRequiredValue = value;
        emit IsVigilanceRequiredChanged(value);
    }
}

// Тяга включена
const bool SystemStateViewModel::getIsTractionOn() const
{
    return isTractionOnValue;
}
void SystemStateViewModel::setIsTractionOn(const bool value)
{
    if (isTractionOnValue != value)
    {
        isTractionOnValue = value;
        emit IsTractionOnChanged(value);
    }
}

// Режим движения (-1 = назад, 0 = стоим, +1 = вперёд)
const int SystemStateViewModel::getDirection() const
{
    return directionValue;
}
void SystemStateViewModel::setDirection(const int value)
{
    if (directionValue != value)
    {
        directionValue = value;
        emit DirectionChanged(value);
    }
}

// Текущая ордината
const int SystemStateViewModel::getOrdinate() const
{
    return ordinateValue;
}
void SystemStateViewModel::setOrdinate(const int value)
{
    if (ordinateValue != value)
    {
        ordinateValue = value;
        emit OrdinateChanged(value);
    }
}

// Тип ближайшей цели
const int SystemStateViewModel::getNextTargetKind() const
{
    return nextTargetKindValue;
}
void SystemStateViewModel::setNextTargetKind(const int value)
{
    if (nextTargetKindValue != value)
    {
        nextTargetKindValue = value;
        emit NextTargetKindChanged(value);
    }
}

// Название ближайшей цели
const QString SystemStateViewModel::getNextTargetName() const
{
    return nextTargetNameValue;
}
void SystemStateViewModel::setNextTargetName(const QString value)
{
    if (nextTargetNameValue != value)
    {
        nextTargetNameValue = value;
        emit NextTargetNameChanged(value);
    }
}

// Расстояние до ближайшей цели
const int SystemStateViewModel::getNextTargetDistance() const
{
    return nextTargetDistanceValue;
}
void SystemStateViewModel::setNextTargetDistance(const int value)
{
    if (nextTargetDistanceValue != value)
    {
        nextTargetDistanceValue = value;
        emit NextTargetDistanceChanged(value);
    }
}

// Текст высокоприоритетного сообщения
const QString SystemStateViewModel::getNotificationText() const
{
    return notificationTextValue;
}
void SystemStateViewModel::setNotificationText(const QString value)
{
    if (notificationTextValue != value)
    {
        notificationTextValue = value;
        emit NotificationTextChanged(value);
    }
}

// Номер пути
const int SystemStateViewModel::getTrackNumber() const
{
    return trackNumberValue;
}
void SystemStateViewModel::setTrackNumber(const int value)
{
    if (trackNumberValue != value)
    {
        trackNumberValue = value;
        emit TrackNumberChanged(value);
    }
}

// Номер машиниста
const int SystemStateViewModel::getMachinistNumber() const
{
    return machinistNumberValue;
}
void SystemStateViewModel::setMachinistNumber(const int value)
{
    if (machinistNumberValue != value)
    {
        machinistNumberValue = value;
        emit MachinistNumberChanged(value);
    }
}

// Номер поезда
const int SystemStateViewModel::getTrainNumber() const
{
    return trainNumberValue;
}
void SystemStateViewModel::setTrainNumber(const int value)
{
    if (trainNumberValue != value)
    {
        trainNumberValue = value;
        emit TrainNumberChanged(value);
    }
}

// Длина поезда в условных вагонах
const int SystemStateViewModel::getWagonCount() const
{
    return wagonCountValue;
}
void SystemStateViewModel::setWagonCount(const int value)
{
    if (wagonCountValue != value)
    {
        wagonCountValue = value;
        emit WagonCountChanged(value);
    }
}

// Длина поезда в осях
const int SystemStateViewModel::getAxlesCount() const
{
    return axlesCountValue;
}
void SystemStateViewModel::setAxlesCount(const int value)
{
    if (axlesCountValue != value)
    {
        axlesCountValue = value;
        emit AxlesCountChanged(value);
    }
}

// Масса поезда
const int SystemStateViewModel::getTrainMass() const
{
    return trainMassValue;
}
void SystemStateViewModel::setTrainMass(const int value)
{
    if (trainMassValue != value)
    {
        trainMassValue = value;
        emit TrainMassChanged(value);
    }
}

// Разрешение ручного ввода начальной ординаты. К сожалению, не используется. Смотрим на номер пути.
const bool SystemStateViewModel::getManualOrdinateEnable() const
{
    return manualOrdinateEnableValue;
}
void SystemStateViewModel::setManualOrdinateEnable(const bool value)
{
    if (manualOrdinateEnableValue != value)
    {
        manualOrdinateEnableValue = value;
        emit ManualOrdinateEnableChanged(value);
    }
}

// Начальная ордината в ручном режиме
const int SystemStateViewModel::getManualOrdinate() const
{
    return manualOrdinateValue;
}
void SystemStateViewModel::setManualOrdinate(const int value)
{
    if (manualOrdinateValue != value)
    {
        manualOrdinateValue = value;
        emit ManualOrdinateChanged(value);
    }
}

// Увеличение ординаты в ручном режиме. 1 - вперёд, 0 - назад.
const int SystemStateViewModel::getManualOrdinateIncreaseDirection() const
{
    return manualOrdinateIncreaseDirectionValue;
}
void SystemStateViewModel::setManualOrdinateIncreaseDirection(const int value)
{
    if (manualOrdinateIncreaseDirectionValue != value)
    {
        manualOrdinateIncreaseDirectionValue = value;
        emit ManualOrdinateIncreaseDirectionChanged(value);
    }
}

// Скорость на белый при ЗАБ
const int SystemStateViewModel::getAutolockSpeed() const
{
    return autolockSpeedValue;
}
void SystemStateViewModel::setAutolockSpeed(const int value)
{
    if (autolockSpeedValue != value)
    {
        autolockSpeedValue = value;
        emit AutolockSpeedChanged(value);
    }
}

// ТСКБМ подключена
const bool SystemStateViewModel::getTsvcIsOnline() const
{
    return tsvcIsOnlineValue;
}
void SystemStateViewModel::setTsvcIsOnline(const bool value)
{
    if (tsvcIsOnlineValue != value)
    {
        tsvcIsOnlineValue = value;
        emit TsvcIsOnlineChanged(value);
    }
}

// ТСКБМ: машинист бодр
const bool SystemStateViewModel::getTsvcIsMachinistCheerful() const
{
    return tsvcIsMachinistCheerfulValue;
}
void SystemStateViewModel::setTsvcIsMachinistCheerful(const bool value)
{
    if (tsvcIsMachinistCheerfulValue != value)
    {
        tsvcIsMachinistCheerfulValue = value;
        emit TsvcIsMachinistCheerfulChanged(value);
    }
}

// ТСКБМ требует подтверждения бдительности
const bool SystemStateViewModel::getTsvcIsVigilanceRequired() const
{
    return tsvcIsVigilanceRequiredValue;
}
void SystemStateViewModel::setTsvcIsVigilanceRequired(const bool value)
{
    if (tsvcIsVigilanceRequiredValue != value)
    {
        tsvcIsVigilanceRequiredValue = value;
        emit TsvcIsVigilanceRequiredChanged(value);
    }
}

// Предварительная сигнализация ТСКБМ активна
const bool SystemStateViewModel::getTsvcIsPreAlarmActive() const
{
    return tsvcIsPreAlarmActiveValue;
}
void SystemStateViewModel::setTsvcIsPreAlarmActive(const bool value)
{
    if (tsvcIsPreAlarmActiveValue != value)
    {
        tsvcIsPreAlarmActiveValue = value;
        emit TsvcIsPreAlarmActiveChanged(value);
    }
}

// -- end: Properties Getters and Setters --





