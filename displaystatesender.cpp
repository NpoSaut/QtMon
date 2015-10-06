#include "displaystatesender.h"

#include "qtBlokLib/parsers/display_state.h"

using namespace Interaction;

DisplayStateSender::DisplayStateSender(Interaction::KeyboardState *keyboardState, ICan *can, QObject *parent) :
    QObject (parent),
    keyboardState (keyboardState),
    can (can),
    backlightLevel (0),
    driveMode (0)
{
    this->startTimer (500);
    QObject::connect(keyboardState, SIGNAL(stateChanged()), this, SLOT(onKeyboardStateChange()));
}

void DisplayStateSender::setValue(double backlightLevel)
{
    this->backlightLevel = backlightLevel;
}

void DisplayStateSender::setDriveMode(int dm)
{
    driveMode = dm;
}

void DisplayStateSender::onKeyboardStateChange()
{
    CanFrame newA = constructA();
    CanFrame newB = constructB();

    if (newA != lastA || newB != lastB)
        sendState(newA, newB);
}

void DisplayStateSender::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    sendState(constructA(), constructB());
}

void DisplayStateSender::sendState(CanFrame A, CanFrame B)
{
    lastA = A;
    can->send (A);
    lastB = B;
    can->send (B);
}

CanFrame DisplayStateSender::constructA()
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
    dsa.setTvk (keyboardState->isPressed(Keyboard::Key::TVK));

    dsa.setBacklightLevel(backlightLevel);
    dsa.setDriveMode (DriveMode(driveMode));

    return dsa.encode();
}

CanFrame DisplayStateSender::constructB()
{
    DisplayStateB dsb;

    dsb.setRb (keyboardState->isPressed (Keyboard::Key::RB));
    dsb.setRbs (keyboardState->isPressed (Keyboard::Key::RBS));

    return dsb.encode();
}
