#include "notificator.h"

Notificator::Notificator(Parser *onParser, QObject *parent) :
    QObject(parent),
    parser(onParser)
{
    this->connect (onParser, SIGNAL(whateverChagned()), SLOT(getStateChangedSignal()));
}


void Notificator::getStateChangedSignal()
{
    if ( !parser->mcoState.isEpvReady () )
        emit notificationTextChanged ("Система отключена");

    else if ( parser->mcoLimits.isTractionShutdown () )
        emit notificationTextChanged ("Экстренное торможение");

    else
        emit notificationTextChanged ("");

//    else if (     blokMessages.mcoLimits.getDriveMode () != ROAD
//         && !blokMessages.ipdState.isInMotion ()             )
//    {
//        // empty for Patriot
//    }

}
