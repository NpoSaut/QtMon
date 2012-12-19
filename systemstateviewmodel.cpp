#include "systemstateviewmodel.h"

SystemStateViewModel::SystemStateViewModel(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    // fileds init start
    speedValue = 48;
    speedRestrictionValue = 60;
    longitudeValue = 60.148;
    latitudeValue = 56.856;
    vigilanceRequiredValue = true;
    // fileds init end
}

// -- start: Properties Getters and Setters --

const double SystemStateViewModel::getSpeedValue() const
{
    return speedValue;
}
void SystemStateViewModel::setSpeedValue(const double value)
{
    if (speedValue != value)
    {
        speedValue = value;
        emit speedChanged();
    }
}

const double SystemStateViewModel::getSpeedRestrictionValue() const
{
    return speedRestrictionValue;
}
void SystemStateViewModel::setSpeedRestrictionValue(const double value)
{
    if (speedRestrictionValue != value)
    {
        speedRestrictionValue = value;
        emit speedRestrictionChanged();
    }
}

const double SystemStateViewModel::getLongitudeValue() const
{
    return longitudeValue;
}
void SystemStateViewModel::setLongitudeValue(const double value)
{
    if (longitudeValue != value)
    {
        longitudeValue = value;
        emit longitudeChanged();
    }
}
const double SystemStateViewModel::getLatitudeValue() const
{
    return latitudeValue;
}
void SystemStateViewModel::setLatitudeValue(const double value)
{
    if (latitudeValue != value)
    {
        latitudeValue = value;
        emit latitudeChanged();
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
// -- end: Properties Getters and Setters --
