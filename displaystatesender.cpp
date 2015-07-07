#include "displaystatesender.h"

#include "qtBlokLib/parsers/display_state.h"

#include "QDebug"

using namespace Interaction;

DisplayStateSender::DisplayStateSender(Interaction::KeyboardState *keyboardState, ICan *can, QObject *parent) :
    QObject (parent),
    keyboardState (keyboardState),
    can (can),
    backlightLevel (0),
    driveMode (0)
{
    this->startTimer (500);
}

void DisplayStateSender::setValue(double backlightLevel)
{
    this->backlightLevel = backlightLevel;
}

void DisplayStateSender::setDriveMode(int dm)
{
    driveMode = dm;
}

void DisplayStateSender::timerEvent(QTimerEvent *event)
{
    DisplayStateA dsa;

    dsa.setRb (keyboardState->isPressed (Keyboard::Key::RB));
    dsa.setRbs (keyboardState->isPressed (Keyboard::Key::RBS));
    dsa.setVk (keyboardState->isPressed (Keyboard::Key::VK));
    dsa.setPull (keyboardState->isPressed (Keyboard::Key::PODT));
    dsa.setOtpr (keyboardState->isPressed (Keyboard::Key::OTPR));
    dsa.setOc (keyboardState->isPressed (Keyboard::Key::OC));
    dsa.setK20 (keyboardState->isPressed (Keyboard::Key::K20));
    dsa.setFreq (keyboardState->isPressed (Keyboard::Key::F));
//    dsa.setTvk (keyboardState->isPressed(Keyboard::Key::TVK));

    dsa.setBacklightLevel(backlightLevel);
    dsa.setDriveMode (DriveMode(driveMode));

    can->send (dsa.encode ());
    qDebug() << dsa.encode().toString().c_str();

    DisplayStateB dsb;
    dsb.setRb (keyboardState->isPressed (Keyboard::Key::RB));
    dsb.setRbs (keyboardState->isPressed (Keyboard::Key::RBS));
    can->send (dsb.encode ());
}
