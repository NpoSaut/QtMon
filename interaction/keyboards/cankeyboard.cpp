#include "cankeyboard.h"

namespace Interaction {
namespace Keyboards {

CanKeyboard::CanKeyboard(ConsoleKey *consoleKey, QObject *parent) :
    consoleKey (consoleKey), Keyboard(parent)
{
    connect (consoleKey, SIGNAL(keyPressed(ConsoleKey::ConsKey)), this, SLOT(consoleKeyPressed(ConsoleKey::ConsKey)));
    connect (consoleKey, SIGNAL(keyReleased(ConsoleKey::ConsKey)), this, SLOT(consoleKeyReleased(ConsoleKey::ConsKey)));
}

void CanKeyboard::consoleKeyPressed(ConsoleKey::ConsKey key)
{
    switch (key) {
    case ConsoleKey::BKSP:
    case ConsoleKey::L: // Установлено опытным путём
        emit backspaceKeyDown();
        emit keyDown(Key::BACKSPACE);
        break;
    case ConsoleKey::ENTER:
        emit enterKeyDown();
        emit keyDown(Key::ENTER);
        break;
    case ConsoleKey::OTM:
        emit cancelKeyDown();
        emit keyDown(Key::CANCEL);
        break;
    case ConsoleKey::K:
        emit commandKeyDown();
        emit keyDown(Key::COMMAND);
        break;
    case ConsoleKey::LGHT:
        emit brightnessKeyDown();
        emit keyDown(Key::K_9);
        break;
    case ConsoleKey::F0:
        emit numberKeyDown(0);
        emit keyDown(Key::K_0);
        break;
    case ConsoleKey::F1:
        emit numberKeyDown(1);
        emit keyDown(Key::K_1);
        break;
    case ConsoleKey::F2:
        emit numberKeyDown(2);
        emit keyDown(Key::K_2);
        break;
    case ConsoleKey::F3:
        emit numberKeyDown(3);
        emit keyDown(Key::K_3);
        break;
    case ConsoleKey::F4:
        emit numberKeyDown(4);
        emit keyDown(Key::K_4);
        break;
    case ConsoleKey::F5:
        emit numberKeyDown(5);
        emit keyDown(Key::K_5);
        break;
    case ConsoleKey::F6:
        emit numberKeyDown(6);
        emit keyDown(Key::K_6);
        break;
    case ConsoleKey::F7:
        emit numberKeyDown(7);
        emit keyDown(Key::K_7);
        break;
    case ConsoleKey::F8:
        emit numberKeyDown(8);
        emit keyDown(Key::K_8);
        break;
    case ConsoleKey::F9:
        emit numberKeyDown(9);
        emit keyDown(Key::K_9);
        break;
    }
}

void CanKeyboard::consoleKeyReleased(ConsoleKey::ConsKey key)
{
    switch (key) {
    case ConsoleKey::BKSP:
    case ConsoleKey::L: // Установлено опытным путём
        emit backspaceKeyUp();
        emit keyUp(Key::BACKSPACE);
        break;
    case ConsoleKey::ENTER:
        emit enterKeyUp();
        emit keyUp(Key::ENTER);
        break;
    case ConsoleKey::OTM:
        emit cancelKeyUp();
        emit keyUp(Key::CANCEL);
        break;
    case ConsoleKey::K:
        emit commandKeyUp();
        emit keyUp(Key::COMMAND);
        break;
    case ConsoleKey::LGHT:
        emit brightnessKeyUp();
        emit keyUp(Key::BRIGHTNESS);
        break;
    case ConsoleKey::F0:
        emit numberKeyUp(0);
        emit keyUp(Key::K_0);
        break;
    case ConsoleKey::F1:
        emit numberKeyUp(1);
        emit keyUp(Key::K_1);
        break;
    case ConsoleKey::F2:
        emit numberKeyUp(2);
        emit keyUp(Key::K_2);
        break;
    case ConsoleKey::F3:
        emit numberKeyUp(3);
        emit keyUp(Key::K_3);
        break;
    case ConsoleKey::F4:
        emit numberKeyUp(4);
        emit keyUp(Key::K_4);
        break;
    case ConsoleKey::F5:
        emit numberKeyUp(5);
        emit keyUp(Key::K_5);
        break;
    case ConsoleKey::F6:
        emit numberKeyUp(6);
        emit keyUp(Key::K_6);
        break;
    case ConsoleKey::F7:
        emit numberKeyUp(7);
        emit keyUp(Key::K_7);
        break;
    case ConsoleKey::F8:
        emit numberKeyUp(8);
        emit keyUp(Key::K_8);
        break;
    case ConsoleKey::F9:
        emit numberKeyUp(9);
        emit keyUp(Key::K_9);
        break;
    }
}



}
}
