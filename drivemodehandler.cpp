#include "drivemodehandler.h"
#include <QDebug>

DrivemodeHandler::DrivemodeHandler(Parser *parser, Can *can, QObject *parent) :
    QObject(parent), parser (parser), can (can),
    target (parser->mcoLimits.getDriveMode ())
{
    QObject::connect (&parser->mcoLimits, SIGNAL(messageReceived()), this, SLOT(processNewState()));
    QObject::connect (&parser->mcoLimits, SIGNAL(driveModeChanged(DriveMode)), this, SLOT(processActualDrivemodeChage(DriveMode)));
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
    qDebug() << "Target mode: " << quint8(tm);
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
            setTarget (TRAIN);
            break;
        case ROAD:
            setTarget (TRAIN);
            break;
    }
}
