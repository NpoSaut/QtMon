#include "compositekeyboard.h"

namespace Interaction {
namespace Keyboards {

CompositeKeyboard::CompositeKeyboard(QVector<Keyboard *> keyboards, QObject *parent) :
    Keyboard(parent)
{
    foreach (Keyboard *keyboard, keyboards) {
        connect (keyboard, SIGNAL(keyDown(Key)), this, SLOT(onKeyDown(Key)));
        connect (keyboard, SIGNAL(keyUp(Key)), this, SLOT(onKeyUp(Key)));
        connect (keyboard, SIGNAL(numberKeyDown(int)), this, SLOT(onNumberKeyDown(int)));
        connect (keyboard, SIGNAL(numberKeyUp(int)), this, SLOT(onNumberKeyUp(int)));
        connect (keyboard, SIGNAL(backspaceKeyDown()), this, SLOT(onBackspaceKeyDown()));
        connect (keyboard, SIGNAL(backspaceKeyUp()), this, SLOT(onBackspaceKeyUp()));
        connect (keyboard, SIGNAL(enterKeyDown()), this, SLOT(onEnterKeyDown()));
        connect (keyboard, SIGNAL(enterKeyUp()), this, SLOT(onEnterKeyUp()));
        connect (keyboard, SIGNAL(cancelKeyDown()), this, SLOT(onCancelKeyDown()));
        connect (keyboard, SIGNAL(cancelKeyUp()), this, SLOT(onCancelKeyUp()));
        connect (keyboard, SIGNAL(commandKeyDown()), this, SLOT(onCommandKeyDown()));
        connect (keyboard, SIGNAL(commandKeyUp()), this, SLOT(onCommandKeyUp()));
        connect (keyboard, SIGNAL(brightnessKeyDown()), this, SLOT(onBrightnessKeyDown()));
        connect (keyboard, SIGNAL(brightnessKeyUp()), this, SLOT(onBrightnessKeyUp()));
    }
}

void CompositeKeyboard::onKeyDown(Keyboard::Key key)
{
    emit keyDown(key);
}

void CompositeKeyboard::onKeyUp(Keyboard::Key key)
{
    emit keyUp(key);
}

void CompositeKeyboard::onNumberKeyDown(int d)
{
    emit numberKeyDown(d);
}

void CompositeKeyboard::onNumberKeyUp(int d)
{
    emit numberKeyUp(d);
}

void CompositeKeyboard::onBackspaceKeyDown()
{
    emit backspaceKeyDown();
}

void CompositeKeyboard::onBackspaceKeyUp()
{
    emit backspaceKeyUp();
}

void CompositeKeyboard::onEnterKeyDown()
{
    emit enterKeyDown();
}

void CompositeKeyboard::onEnterKeyUp()
{
    emit enterKeyUp();
}

void CompositeKeyboard::onCancelKeyDown()
{
    emit cancelKeyDown();
}

void CompositeKeyboard::onCancelKeyUp()
{
    emit cancelKeyUp();
}

void CompositeKeyboard::onCommandKeyDown()
{
    emit commandKeyDown();
}

void CompositeKeyboard::onCommandKeyUp()
{
    emit commandKeyUp();
}

void CompositeKeyboard::onBrightnessKeyDown()
{
    emit brightnessKeyDown();
}

void CompositeKeyboard::onBrightnessKeyUp()
{
    emit brightnessKeyUp();
}

}
}
