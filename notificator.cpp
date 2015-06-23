#include "notificator.h"

Notificator::Notificator(bool handbrakeHintRequired, Parser *onParser, QObject *parent) :
    QObject(parent),
    parser(onParser),
    handbrakeHintRequired (handbrakeHintRequired)
{
    this->connect (onParser, SIGNAL(whateverChagned()), SLOT(getStateChangedSignal()));

    if (handbrakeHintRequired)
    {
        handbrakeHintTimeout.setSingleShot (true);
        handbrakeHintTimeout.setInterval (15000);
        this->connect (&handbrakeHintTimeout, SIGNAL(timeout()), SLOT(handbrakeHintShow()));
    }
}


void Notificator::getStateChangedSignal()
{
    if (handbrakeHintRequired)
    {
        // Подними ручник
        if ( parser->mcoLimits.getDriveMode () != ROAD
         && !parser->ipdState.isInMotion ()
         &&  parser->mcoState.isTraction ()  )
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

    if ( !parser->mcoState.isEpvReady () )
        emit notificationTextChanged ("Система отключена");

    else if ( parser->mcoLimits.isTractionShutdownCommand () )
        emit notificationTextChanged ("Экстренное торможение");

    else if ( handbrakeHint )
        emit notificationTextChanged ("Подними ручник");

    else
        emit notificationTextChanged ("");
}

void Notificator::handbrakeHintShow()
{
    handbrakeHint = true;
    getStateChangedSignal ();
}
