#include "notificator.h"

Notificator::Notificator (QObject *parent) :
    QObject (parent),
    handbrakeHintTimeout (), handbrakeHint (false)
{
    this->connect (&blokMessages, SIGNAL(whateverChagned()), SLOT(getStateChangedSignal()));

    handbrakeHintTimeout.setSingleShot (true);
    handbrakeHintTimeout.setInterval (15);
    this->connect (&handbrakeHintTimeout, SIGNAL(timeout()), SLOT(handbrakeHintShow()));
}


void Notificator::getStateChangedSignal()
{
    if ( !blokMessages.mcoState.isEpvReady () )
        emit notificationTextChanged ("Система отключена");

    else if ( blokMessages.mcoLimits.isTractionShutdown () )
        emit notificationTextChanged ("Экстренное торможение");

    else if ( handbrakeHint )
        emit notificationTextChanged ("Подними ручник");

    else
        emit notificationTextChanged ("");

    // Подними ручник
    if ( blokMessages.mcoLimits.getDriveMode () != ROAD
     &&  !blokMessages.ipdState.isInMotion ()             )
    {
        if ( !handbrakeHintTimeout.isActive () )
            handbrakeHintTimeout.start ();
    }
    else
    {
        handbrakeHintTimeout.stop ();
        handbrakeHint = false;
    }

}

void Notificator::handbrakeHintShow()
{
    handbrakeHint = true;
}
