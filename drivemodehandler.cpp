#include "drivemodehandler.h"
#include <QDebug>

DrivemodeHandler::DrivemodeHandler(Parser *parser, Can *can, QObject *parent) :
    QObject(parent), parser (parser), can (can),
    target (parser->mcoLimits.getDriveMode ())
{
    QObject::connect (&parser->mcoLimits, SIGNAL(messageReceived()), this, SLOT(processNewState()));
    QObject::connect (&parser->mcoLimits, SIGNAL(driveModeChanged(DriveMode)), this, SLOT(processActualDrivemodeChage(DriveMode)));
    QObject::connect (&parser->vdsState, SIGNAL(ironWheelsChagned(bool)), this, SLOT(processIronWheelsChange(bool)));
}

void DrivemodeHandler::processIronWheelsChange(bool ironWheels)
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

void DrivemodeHandler::processActualDrivemodeChage(DriveMode dm)
{
    emit actualDrivemodeChanged (quint8(dm));
}

void DrivemodeHandler::processNewState()
{
    if ( parser->mcoLimits.getDriveMode () != target )
    {
        if (++convergenceCounter >= 2)
        {
            convergenceCounter = 0;
            can->transmitMessage (SysKey(SysKey::RMP, SysKey::PRESS).encode ());
        }
    }
}

void DrivemodeHandler::setTarget(DriveMode tm)
{
    if ( target != tm )
    {
        target = tm;
        emit targetDrivemodeChanged (quint8(target));
    }
}

DriveMode DrivemodeHandler::getTarget() const
{
    return target;
}

void DrivemodeHandler::drivemodeChangeButtonPressed()
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
