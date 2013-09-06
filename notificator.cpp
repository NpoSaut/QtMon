#include "notificator.h"

Notificator::Notificator(QObject *parent) :
    QObject(parent)
{
    this->connect (&blokMessages, SIGNAL(whateverChagned()), SLOT(getStateChangedSignal()));
}


void Notificator::getStateChangedSignal()
{
    if ( !blokMessages.mcoState.isEpvReady () )
        emit notificationTextChanged ("Система отключена");

    else if ( blokMessages.mcoLimits.isTractionShutdown () )
        emit notificationTextChanged ("Экстренное торможение");

    else
        emit notificationTextChanged ("");

//    else if (     blokMessages.mcoLimits.getDriveMode () != ROAD
//         && !blokMessages.ipdState.isInMotion ()             )
//    {
//        // empty for Patriot
//    }

}
