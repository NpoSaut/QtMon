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
    pressureTCValue = "0.00";
    pressureTMValue = "0.00";
    longitudeValue = 60.4688;
    latitudeValue = 56.88397;
    systemWarningLevelValue = 0;
    fullSetWarningLevelValue = 0;
    isPressureOkValue = true;
    isEpvReadyValue = true;
    isEpvReleasedValue = false;
    milageValue = 0;
    lightValue = -2;
    alsnFreqTargetValue = -1;
    alsnFreqFactValue = -1;
    autolockTypeTargetValue = -1;
    autolockTypeFactValue = -1;
    timeValue = "-:-";
    dateValue = "- / - / -";
    isRegistrationTapeActiveValue = false;
    driveModeTargetValue = 0;
    driveModeFactValue = -1;
    ironWheelsValue = true;
    isVigilanceRequiredValue = true;
    isTractionOnValue = false;
    directionValue = 0;
    warningTextValue = "";
    infoTextValue = "";
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
        emit SpeedChanged();
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
        emit SpeedIsValidChanged();
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
        emit SpeedFromSkyChanged();
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
        emit SpeedFromEarthChanged();
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
        emit SpeedRestrictionChanged();
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
        emit TargetSpeedChanged();
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
        emit AccelerationChanged();
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
        emit PressureTCChanged();
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
        emit PressureTMChanged();
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
        emit LongitudeChanged();
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
        emit LatitudeChanged();
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
        emit SystemWarningLevelChanged();
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
        emit FullSetWarningLevelChanged();
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
        emit IsPressureOkChanged();
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
        emit IsEpvReadyChanged();
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
        emit IsEpvReleasedChanged();
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
        emit MilageChanged();
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
        emit LightChanged();
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
        emit AlsnFreqTargetChanged();
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
        emit AlsnFreqFactChanged();
    }
}

// Целевой тип автоблокировки
const int SystemStateViewModel::getAutolockTypeTarget() const
{
    return autolockTypeTargetValue;
}
void SystemStateViewModel::setAutolockTypeTarget(const int value)
{
    if (autolockTypeTargetValue != value)
    {
        autolockTypeTargetValue = value;
        emit AutolockTypeTargetChanged();
    }
}

// Фактический тип автоблокировки
const int SystemStateViewModel::getAutolockTypeFact() const
{
    return autolockTypeFactValue;
}
void SystemStateViewModel::setAutolockTypeFact(const int value)
{
    if (autolockTypeFactValue != value)
    {
        autolockTypeFactValue = value;
        emit AutolockTypeFactChanged();
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
        emit TimeChanged();
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
        emit DateChanged();
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
        emit IsRegistrationTapeActiveChanged();
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
        emit driveModeTargetChanged();
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
        emit driveModeFactChanged();
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
        emit IronWheelsChanged();
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
        emit IsVigilanceRequiredChanged();
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
        emit IsTractionOnChanged();
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
        emit DirectionChanged();
    }
}

// Текст высокоприоритетного сообщения
const QString SystemStateViewModel::getWarningText() const
{
    return warningTextValue;
}
void SystemStateViewModel::setWarningText(const QString value)
{
    if (warningTextValue != value)
    {
        warningTextValue = value;
        emit WarningTextChanged();
    }
}

// Текст низкоприоритетного сообщения
const QString SystemStateViewModel::getInfoText() const
{
    return infoTextValue;
}
void SystemStateViewModel::setInfoText(const QString value)
{
    if (infoTextValue != value)
    {
        infoTextValue = value;
        emit InfoTextChanged();
    }
}

// -- end: Properties Getters and Setters --





