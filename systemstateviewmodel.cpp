#include "systemstateviewmodel.h"

SystemStateViewModel::SystemStateViewModel(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    // fileds init start
    getspeedValue = 48;
    getspeedRestrictionValue = 65;
    getlongitudeValue = 60.148;
    getlatitudeValue = 56.856;
    getisVigilanceRequiredValue = true;
    getsystemWarningLevelValue = 0;
    getfullSetWarningLevelValue = 0;
    getisPressureOkValue = true;
    getisEpvReadyValue = true;
    getisEpvReleasedValue = false;
    getmilageValue = 0;
    getlightValue = 0;
    getalsnFreqValue = 25;
    gettimeValue = "18:58";
    getdateValue = "21.12.2012";
    getpropertyViewValue = false;
    // fileds init end
}

// -- start: Properties Getters and Setters --
// Текущая скорость
const double SystemStateViewModel::getSpeed() const
{
    return getspeedValue;
}
void SystemStateViewModel::setSpeed(const double value)
{
    if (getspeedValue != value)
    {
        getspeedValue = value;
        emit SpeedChanged();
    }
}

// Ограничение скорости
const double SystemStateViewModel::getSpeedRestriction() const
{
    return getspeedRestrictionValue;
}
void SystemStateViewModel::setSpeedRestriction(const double value)
{
    if (getspeedRestrictionValue != value)
    {
        getspeedRestrictionValue = value;
        emit SpeedRestrictionChanged();
    }
}

const double SystemStateViewModel::getLongitude() const
{
    return getlongitudeValue;
}
void SystemStateViewModel::setLongitude(const double value)
{
    if (getlongitudeValue != value)
    {
        getlongitudeValue = value;
        emit LongitudeChanged();
    }
}

const double SystemStateViewModel::getLatitude() const
{
    return getlatitudeValue;
}
void SystemStateViewModel::setLatitude(const double value)
{
    if (getlatitudeValue != value)
    {
        getlatitudeValue = value;
        emit LatitudeChanged();
    }
}

// Необходимость подтверждения бдительности
const bool SystemStateViewModel::getIsVigilanceRequired() const
{
    return getisVigilanceRequiredValue;
}
void SystemStateViewModel::setIsVigilanceRequired(const bool value)
{
    if (getisVigilanceRequiredValue != value)
    {
        getisVigilanceRequiredValue = value;
        emit IsVigilanceRequiredChanged();
    }
}

// Общий уровень предупреждений
const int SystemStateViewModel::getSystemWarningLevel() const
{
    return getsystemWarningLevelValue;
}
void SystemStateViewModel::setSystemWarningLevel(const int value)
{
    if (getsystemWarningLevelValue != value)
    {
        getsystemWarningLevelValue = value;
        emit SystemWarningLevelChanged();
    }
}

// Укомплектованность конфигурации
const int SystemStateViewModel::getFullSetWarningLevel() const
{
    return getfullSetWarningLevelValue;
}
void SystemStateViewModel::setFullSetWarningLevel(const int value)
{
    if (getfullSetWarningLevelValue != value)
    {
        getfullSetWarningLevelValue = value;
        emit FullSetWarningLevelChanged();
    }
}

// Давление в норме
const bool SystemStateViewModel::getIsPressureOk() const
{
    return getisPressureOkValue;
}
void SystemStateViewModel::setIsPressureOk(const bool value)
{
    if (getisPressureOkValue != value)
    {
        getisPressureOkValue = value;
        emit IsPressureOkChanged();
    }
}

// Готовность ЭПК
const bool SystemStateViewModel::getIsEpvReady() const
{
    return getisEpvReadyValue;
}
void SystemStateViewModel::setIsEpvReady(const bool value)
{
    if (getisEpvReadyValue != value)
    {
        getisEpvReadyValue = value;
        emit IsEpvReadyChanged();
    }
}

// Признак срыва ЭПК
const bool SystemStateViewModel::getIsEpvReleased() const
{
    return getisEpvReleasedValue;
}
void SystemStateViewModel::setIsEpvReleased(const bool value)
{
    if (getisEpvReleasedValue != value)
    {
        getisEpvReleasedValue = value;
        emit IsEpvReleasedChanged();
    }
}

// Проиденное расстояние
const int SystemStateViewModel::getMilage() const
{
    return getmilageValue;
}
void SystemStateViewModel::setMilage(const int value)
{
    if (getmilageValue != value)
    {
        getmilageValue = value;
        emit MilageChanged();
    }
}

// Код сигнала светофора (0 - К, 1 - КЖ, ...)
const int SystemStateViewModel::getLight() const
{
    return getlightValue;
}
void SystemStateViewModel::setLight(const int value)
{
    if (getlightValue != value)
    {
        getlightValue = value;
        emit LightChanged();
    }
}

// Частота АЛСН
const int SystemStateViewModel::getAlsnFreq() const
{
    return getalsnFreqValue;
}
void SystemStateViewModel::setAlsnFreq(const int value)
{
    if (getalsnFreqValue != value)
    {
        getalsnFreqValue = value;
        emit AlsnFreqChanged();
    }
}

// Время
const QString SystemStateViewModel::getTime() const
{
    return gettimeValue;
}
void SystemStateViewModel::setTime(const QString value)
{
    if (gettimeValue != value)
    {
        gettimeValue = value;
        emit TimeChanged();
    }
}

// Дата
const QString SystemStateViewModel::getDate() const
{
    return getdateValue;
}
void SystemStateViewModel::setDate(const QString value)
{
    if (getdateValue != value)
    {
        getdateValue = value;
        emit DateChanged();
    }
}

// Неведомо чудо
const bool SystemStateViewModel::getPropertyView() const
{
    return getpropertyViewValue;
}
void SystemStateViewModel::setPropertyView(const bool value)
{
    if (getpropertyViewValue != value)
    {
        getpropertyViewValue = value;
        emit PropertyViewChanged();
    }
}

// -- end: Properties Getters and Setters --





