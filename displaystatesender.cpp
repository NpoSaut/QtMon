#include "displaystatesender.h"

#include "qtBlokLib/parsers/display_state.h"

#include <QDebug>

DisplayStateSander::DisplayStateSander(Parser *parser, Can *can, QObject *parent) :
    QObject(parent),
    can (can),
    parser (parser)
{
    this->startTimer (500);
}

void DisplayStateSander::timerEvent(QTimerEvent *event)
{
    DisplayStateA dsa;
    dsa.setRb (parser->sysKey.isKeyPressed (SysKey::RB));
    dsa.setRbs (parser->sysKey.isKeyPressed (SysKey::RBS));
    dsa.setVk (parser->sysKey.isKeyPressed (SysKey::VK));
//    dsa.setDriveMode (parser->sysKey.isKeyPressed (SysKey::));
    dsa.setPull (parser->sysKey.isKeyPressed (SysKey::PULL));
    dsa.setOtpr (parser->sysKey.isKeyPressed (SysKey::OTPR));
    dsa.setOc (parser->sysKey.isKeyPressed (SysKey::OC));
    dsa.setK20 (parser->sysKey.isKeyPressed (SysKey::K20));
    dsa.setFreq (parser->sysKey.isKeyPressed (SysKey::FREQ));

    can->transmitMessage (dsa.encode ());

    CanFrame dispStateB (0x53E2, // id: 0x29F
                    std::vector<unsigned char> (2, 0) );
    can->transmitMessage (dispStateB);
}
