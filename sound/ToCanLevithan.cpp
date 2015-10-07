#include "ToCanLevithan.h"

#include "qtBlokLib/parsers/console_beep.h"

using namespace Sound;

ToCanLevithan::ToCanLevithan(ICan *can, QObject *parent) :
    ILevithan(parent),
    can (can)
{
}

void ToCanLevithan::beep()
{
    ConsoleBeep message;
    can->send(message.encode());
}

