#include "drivemodehandler.h"
#include <QDebug>

DrivemodePassHandler::DrivemodePassHandler(Parser *parser, QObject *parent) :
    DrivemodeHandler(parent)
{
    QObject::connect(&parser->mcoLimits, SIGNAL(driveModeChanged(DriveMode)), this, SLOT(convertEnumToInt(DriveMode)));
}

void DrivemodePassHandler::convertEnumToInt(DriveMode dm)
{
    emit actualDrivemodeChanged(int (dm));
}

DrivemodeSettingHandler::DrivemodeSettingHandler(Parser *parser, Can *can, QObject *parent) :
    DrivemodeHandler(parent), parser (parser), can (can),
    target (parser->mcoLimits.getDriveMode ()),
    convergenceCounter (0)
{
    QObject::connect (&parser->mcoLimits, SIGNAL(messageReceived()), this, SLOT(processNewState()));
    QObject::connect (&parser->mcoLimits, SIGNAL(driveModeChanged(DriveMode)), this, SLOT(processActualDrivemodeChage(DriveMode)));
    QObject::connect (&parser->vdsState, SIGNAL(ironWheelsChagned(bool)), this, SLOT(processIronWheelsChange(bool)));
}

void DrivemodeSettingHandler::processIronWheelsChange(bool ironWheels)
{
    if (ironWheels)
    {
        if (getTarget () == ROAD)
            setTarget (TRAIN);
    }
    else
    {
        setTarget (ROAD);
    }
}

void DrivemodeSettingHandler::processActualDrivemodeChage(DriveMode dm)
{
    emit actualDrivemodeChanged (quint8(dm));
}

void DrivemodeSettingHandler::processNewState()
{
    if ( parser->mcoLimits.getDriveMode () != target )
    {
        if (++convergenceCounter >= 2)
        {
            convergenceCounter = 0;
            can->transmitMessage (SysKey(SysKey::RMP, SysKey::PRESS).encode ());
        }
    }
    else
    {
        convergenceCounter = 0;
    }
}

void DrivemodeSettingHandler::setTarget(DriveMode tm)
{
    if ( target != tm )
    {
        target = tm;
        emit targetDrivemodeChanged (quint8(target));
    }
}

DriveMode DrivemodeSettingHandler::getTarget() const
{
    return target;
}

void DrivemodeSettingHandler::drivemodeChangeButtonPressed()
{
    switch(getTarget ())
    {
        case TRAIN:
            setTarget (SHUNTING);
            break;
        case SHUNTING:
            setTarget (WORKING);
            break;
        case WORKING:
        case DOUBLE_TRACTION:
            if (parser->vdsState.isIronWheels ())
                setTarget (TRAIN);
            else
                setTarget (ROAD);
            break;
        case ROAD:
            setTarget (TRAIN);
            break;
    }
}

