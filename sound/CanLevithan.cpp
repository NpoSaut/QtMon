#include "CanLevithan.h"

#include "qtBlokLib/parsers/console_beep.h"

using namespace Sound;

CanLevithan::CanLevithan(ICan *can, QObject *parent) :
    ILevithan(parent),
    can (can)
{
}

void CanLevithan::beep()
{
    ConsoleBeep message;
    can->send(message.encode());
}

