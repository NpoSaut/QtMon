#include "KeyboardState.h"

using namespace Interaction;

KeyboardState::KeyboardState(Keyboard *keyboard, QObject *parent)
    : QObject (parent),
      pressedKeys ()
{
   pressedKeys.reserve(24);
   QObject::connect(keyboard, SIGNAL(keyDown(Interaction::Keyboard::Key)), this, SLOT(keyDown(Interaction::Keyboard::Key)));
   QObject::connect(keyboard, SIGNAL(keyUp(Interaction::Keyboard::Key)), this, SLOT(keyUp(Interaction::Keyboard::Key)));
}

bool KeyboardState::isPressed(Keyboard::Key key)
{
    return pressedKeys.indexOf(key) != -1;
}

void KeyboardState::keyDown(Interaction::Keyboard::Key key)
{
    pressedKeys.append(key);
    emit stateChanged();
}

void KeyboardState::keyUp(Interaction::Keyboard::Key key)
{
    // Удаляет все
    for (int e = pressedKeys.indexOf(key); e != -1; e = pressedKeys.indexOf(key))
    {
        pressedKeys.remove(e);
        emit stateChanged();
    }
}
