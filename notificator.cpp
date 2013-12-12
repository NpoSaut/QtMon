#include "notificator.h"

Notificator::Notificator(Parser *onParser, QObject *parent) :
    QObject(parent),
    parser(onParser)
{
    this->connect (onParser, SIGNAL(whateverChagned()), SLOT(getStateChangedSignal()));

    handbrakeHintTimeout.setSingleShot (true);
    handbrakeHintTimeout.setInterval (15000);
    this->connect (&handbrakeHintTimeout, SIGNAL(timeout()), SLOT(handbrakeHintShow()));
}


void Notificator::getStateChangedSignal()
{
    if ( !parser->mcoState.isEpvReady () )
        emit notificationTextChanged ("Система отключена");

    else if ( parser->mcoLimits.isTractionShutdownCommand () )
        emit notificationTextChanged ("Экстренное торможение");

    else if ( handbrakeHint )
        emit notificationTextChanged ("Подними ручник");

    else
        emit notificationTextChanged ("");

    // Подними ручник
    if ( blokMessages.mcoLimits.getDriveMode () != ROAD
     &&  !blokMessages.ipdState.isInMotion ()
     &&  blokMessages.mcoState.isTraction ()  )
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
