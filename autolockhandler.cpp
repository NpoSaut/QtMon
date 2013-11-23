#include "autolockhandler.h"

AutolockHandler::AutolockHandler(Can *can, Parser *parser, QObject *parent) :
    QObject(parent),
    can (can),
    parser (parser),
    target (AB),
    speed (0),
    init (true)
{
    QObject::connect (&parser->mpState, SIGNAL(messageReceived()), this, SLOT(proccessMpMessage()));
    QObject::connect (&parser->mpState, SIGNAL(autoblockClosedChanged(bool)), this, SLOT(proccessAutolockStateChange()));
    QObject::connect (&parser->mpState, SIGNAL(autoblockSemiClosedChanged(bool)), this, SLOT(proccessAutolockStateChange()));
}

void AutolockHandler::setTargetMode(int mode)
{
    target = AutolockMode(mode);
}

void AutolockHandler::setWhiteSpeed(int s)
{
    speed = s;
}

void AutolockHandler::proccessMpMessage()
{
    AutolockMode actual = getMpAutolockState ();
    if ( init )
    {
        init = false;
        emit targetAutlockModeChanged (int (actual));
    }
    else if ( actual != target )
    {
        CanFrame frame (0x8D07);
        frame[1] = 0x03;

        switch (target) {
        case AB:
            frame[2] = 0x20;
            break;
        case PAB:
            frame[2] = 0x29;
            frame[3] = speed;
            frame[4] = speed/256;
            break;
        case ZAB:
            frame[2] = 0x1F;
            frame[3] = speed;
            frame[4] = speed/256;
            break;
        default:
            break;
        }

        can->transmitMessage (frame);
    }
}

void AutolockHandler::proccessAutolockStateChange()
{
    emit actualAutolockModeChanged (int (getMpAutolockState ()));
}

AutolockHandler::AutolockMode AutolockHandler::getMpAutolockState() const
{
    return AutolockMode (
                      (quint8 (parser->mpState.isAutoblockClosed ()) << 1)
                    | (quint8 (parser->mpState.isAutoblockSemiClosed ()) << 0)
                            );
}


