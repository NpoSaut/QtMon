#include "keyretranslator.h"

KeyRetranslator::KeyRetranslator(Can *can, QObject *parent) :
    QObject(parent), can (can)
{ }

void KeyRetranslator::catchKeyPress(ConsoleKey::ConsKey key)
{
    can->transmitMessage(SysKey(convert(key), SysKey::PRESS, this).encode());
}

void KeyRetranslator::catchKeyReleased(ConsoleKey::ConsKey key)
{
    can->transmitMessage(SysKey(convert(key), SysKey::RELEASE, this).encode());
}

SysKey::Key KeyRetranslator::convert(ConsoleKey::ConsKey key)
{
    switch (key) {
    case ConsoleKey::RB:
        return SysKey::RB;
    case ConsoleKey::RBS:
        return SysKey::RBS;
    case ConsoleKey::VK:
        return SysKey::VK;
    case ConsoleKey::RMP:
        return SysKey::RMP;
    case ConsoleKey::F:
        return SysKey::FREQ;
    case ConsoleKey::POD:
        return SysKey::PULL;
    case ConsoleKey::OTPR:
        return SysKey::OTPR;
    case ConsoleKey::OC:
        return SysKey::OC;
    case ConsoleKey::K20:
        return SysKey::K20;
    default:
        return SysKey::DUMMY;
    }
}
