#include "systemstateviewmodel.h"

SystemStateViewModel::SystemStateViewModel(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    // fileds init start
    speedValue = 48;
    speedRestrictionValue = 65;
    longitudeValue = 60.47;
    latitudeValue = 56.883;
    vigilanceRequiredValue = true;
    systemWarningLevelValue = 0;
    fullSetWarningLevelValue = 0;
    pressureOkValue = true;
    epvReadyValue = true;
    epvReleasedValue = false;
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

// -- end: Properties Getters and Setters --
