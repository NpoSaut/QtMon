#include "CanLevithan.h"

#include "qtBlokLib/parsers/console_beep.h"

CanLevithan::CanLevithan(ICan *can, QObject *parent) :
    Levithan(parent),
    can (can)
{
}

void CanLevithan::beepHigh()
{
    ConsoleBeep message;
    can->send(message.encode());
}

