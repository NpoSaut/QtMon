#include "drivemodehandler.h"
#include <QDebug>

DrivemodeHandler::DrivemodeHandler(Parser *parser, Can *can, QObject *parent) :
    QObject(parent), parser (parser), can (can),
    target (parser->mcoLimits.getDriveMode ()),
    init (true)
{
    QObject::connect (&parser->mcoLimits, SIGNAL(messageReceived()), this, SLOT(processNewState()));
    QObject::connect (&parser->mcoLimits, SIGNAL(driveModeChanged(DriveMode)), this, SLOT(processActualDrivemodeChage(DriveMode)));
}

void DrivemodeHandler::proccessNewTargetDrivemode(int dm)
{
    setTarget (DriveMode (dm));
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
    if ( init )
    {
        init = false;
        emit targetDrivemodeChanged (quint8 (parser->mcoLimits.getDriveMode ()));
    }
    else if ( parser->mcoLimits.getDriveMode () != target )
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
        case HILL:
            setTarget (TRAIN);
            break;
        case ROAD:
            setTarget (TRAIN);
            break;
    }
}

