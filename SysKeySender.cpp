#include "SysKeySender.h"

using namespace Interaction;

SysKeySender::SysKeySender(Interaction::Keyboard *keyboard, ICan *can, QObject *parent) :
    QObject(parent),
    can (can),
    map ()
{   
    QObject::connect(keyboard, SIGNAL(keyDown(Interaction::Keyboard::Key)), this, SLOT(keyDown(Interaction::Keyboard::Key)));
    QObject::connect(keyboard, SIGNAL(keyUp(Interaction::Keyboard::Key)), this, SLOT(keyUp(Interaction::Keyboard::Key)));

    map[Keyboard::RB] = SysKey::RB;
    map[Keyboard::RBS] = SysKey::RBS;
    map[Keyboard::VK] = SysKey::VK;
    map[Keyboard::RMP] = SysKey::RMP;
    map[Keyboard::F] = SysKey::FREQ;
    map[Keyboard::PODT] = SysKey::PULL;
    map[Keyboard::OTPR] = SysKey::OTPR;
    map[Keyboard::OC] = SysKey::OC;
    map[Keyboard::K20] = SysKey::K20;
}

void SysKeySender::keyDown(Interaction::Keyboard::Key key)
{
    if (map.contains(key))
    {
        SysKey sysKey (map[key], SysKey::Action::PRESS, this);
        can->send( sysKey.encode() );
    }
}

void SysKeySender::keyUp(Interaction::Keyboard::Key key)
{
    if (map.contains(key))
    {
        SysKey sysKey (map[key], SysKey::Action::RELEASE, this);
        can->send( sysKey.encode() );
    }
}
