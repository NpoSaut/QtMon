#include "systemstateviewmodel.h"

SystemStateViewModel::SystemStateViewModel(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    // fileds init start
    speedValue = 50;
    speedRestrictionValue = 65;
    longitudeValue = 60.47;
    latitudeValue = 56.883;
    vigilanceRequiredValue = true;
    systemWarningLevelValue = 0;
    fullSetWarningLevelValue = 0;
    pressureOkValue = true;
    epvReadyValue = true;
    epvReleasedValue = false;
    propertyView = false;
    light = 0;
    time = "21:11";
    date = "28 декабря 2012";
    milage = 0;
    alsnFreq = 25;
    // fileds init end
}

// -- start: Properties Getters and Setters --
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

const double SystemStateViewModel::getSpeedRestriction() const
{
    return speedRestrictionValue;
}
void SystemStateViewModel::setSpeedRestriction(const double value)
{
    if (speedRestrictionValue != value)
    {
        speedRestrictionValue = value;
        emit SpeedRestrictionChanged();
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

const bool SystemStateViewModel::getIsVigilanceRequired() const
{
    return vigilanceRequiredValue;
}
void SystemStateViewModel::setIsVigilanceRequired(const bool value)
{
    if (vigilanceRequiredValue != value)
    {
        vigilanceRequiredValue = value;
        emit IsVigilanceRequiredChanged();
    }
}

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

const bool SystemStateViewModel::getIsPressureOk() const
{
    return pressureOkValue;
}
void SystemStateViewModel::setIsPressureOk(const bool value)
{
    if (pressureOkValue != value)
    {
        pressureOkValue = value;
        emit IsPressureOkChanged();
    }
}

const bool SystemStateViewModel::getIsEpvReady() const
{
    return epvReadyValue;
}
void SystemStateViewModel::setIsEpvReady(const bool value)
{
    if (epvReadyValue != value)
    {
        epvReadyValue = value;
        emit IsEpvReadyChanged();
    }
}

const bool SystemStateViewModel::getIsEpvReleased() const
{
    return epvReleasedValue;
}
void SystemStateViewModel::setIsEpvReleased(const bool value)
{
    if (epvReleasedValue != value)
    {
        epvReleasedValue = value;
        emit IsEpvReleasedChanged();
    }
}

const bool SystemStateViewModel::getPropertyView() const
{
    return propertyView;
}
void SystemStateViewModel::setPropertyView(const bool value)
{
    if (propertyView != value)
    {
        propertyView = value;
        emit PropertyViewChanged();
    }
}

const int SystemStateViewModel::getLight() const
{
    return light;
}
void SystemStateViewModel::setLight(const int value)
{
    if (light != value)
    {
        light = value;
        emit LightChanged();
    }
}

const QString SystemStateViewModel::getTime() const
{
    return time;
}
void SystemStateViewModel::setTime(const QString value)
{
    if (time != value)
    {
        time = value;
        emit TimeChanged();
    }
}

const QString SystemStateViewModel::getDate() const
{
    return date;
}
void SystemStateViewModel::setDate(const QString value)
{
    if (date != value)
    {
        date = value;
        emit DateChanged();
    }
}

const int SystemStateViewModel::getMilage() const
{
    return milage;
}
void SystemStateViewModel::setMilage(const int value)
{
    if (milage != value)
    {
        milage = value;
        emit MilageChanged();
    }
}

const int SystemStateViewModel::getAlsnFreq() const
{
    return alsnFreq;
}
void SystemStateViewModel::setAlsnFreq(const int value)
{
    if (alsnFreq != value)
    {
        alsnFreq = value;
        emit AlsnFreqChanged();
    }
}

// -- end: Properties Getters and Setters --
