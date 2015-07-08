#include "cankeyboard.h"

namespace Interaction {
namespace Keyboards {

CanKeyboard::CanKeyboard(ConsoleKey *consoleKey, QObject *parent) :
    Keyboard(parent), consoleKey (consoleKey)
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
        emit keyDown(Keyboard::Key::BACKSPACE);
        break;
    case ConsoleKey::ENTER:
        emit enterKeyDown();
        emit keyDown(Keyboard::Key::ENTER);
        break;
    case ConsoleKey::OTM:
        emit cancelKeyDown();
        emit keyDown(Keyboard::Key::CANCEL);
        break;
    case ConsoleKey::K:
        emit commandKeyDown();
        emit keyDown(Keyboard::Key::COMMAND);
        break;
    case ConsoleKey::LGHT:
        emit brightnessKeyDown();
        emit keyDown(Keyboard::Key::BRIGHTNESS);
        break;
    case ConsoleKey::F0:
        emit numberKeyDown(0);
        emit keyDown(Keyboard::Key::K_0);
        break;
    case ConsoleKey::F1:
        emit numberKeyDown(1);
        emit keyDown(Keyboard::Key::K_1);
        break;
    case ConsoleKey::F2:
        emit numberKeyDown(2);
        emit keyDown(Keyboard::Key::K_2);
        break;
    case ConsoleKey::F3:
        emit numberKeyDown(3);
        emit keyDown(Keyboard::Key::K_3);
        break;
    case ConsoleKey::F4:
        emit numberKeyDown(4);
        emit keyDown(Keyboard::Key::K_4);
        break;
    case ConsoleKey::F5:
        emit numberKeyDown(5);
        emit keyDown(Keyboard::Key::K_5);
        break;
    case ConsoleKey::F6:
        emit numberKeyDown(6);
        emit keyDown(Keyboard::Key::K_6);
        break;
    case ConsoleKey::F7:
        emit numberKeyDown(7);
        emit keyDown(Keyboard::Key::K_7);
        break;
    case ConsoleKey::F8:
        emit numberKeyDown(8);
        emit keyDown(Keyboard::Key::K_8);
        break;
    case ConsoleKey::F9:
        emit numberKeyDown(9);
        emit keyDown(Keyboard::Key::K_9);
        break;
    case ConsoleKey::P:
        emit pKeyDown();
        emit keyDown(Keyboard::Key::P);
        break;
    case ConsoleKey::VK:
        emit vkKeyDown();
        emit keyDown(Keyboard::Key::VK);
        break;
    case ConsoleKey::RMP:
        emit rmpKeyDown();
        emit keyDown(Keyboard::Key::RMP);
        break;
    case ConsoleKey::F:
        emit fKeyDown();
        emit keyDown(Keyboard::Key::F);
        break;
    case ConsoleKey::TVK:
        emit tvkKeyDown();
        emit keyDown(Keyboard::Key::TVK);
        break;
    case ConsoleKey::K20:
        emit k20KeyDown();
        emit keyDown(Keyboard::Key::K20);
        break;
    case ConsoleKey::OC:
        emit ocKeyDown();
        emit keyDown(Keyboard::Key::OC);
        break;
    case ConsoleKey::OTPR:
        emit otprKeyDown();
        emit keyDown(Keyboard::Key::OTPR);
        break;
    case ConsoleKey::POD:
        emit podtKeyDown();
        emit keyDown(Keyboard::Key::PODT);
        break;
    case ConsoleKey::RB:
        emit rbKeyDown();
        emit keyDown(Keyboard::Key::RB);
        break;
    case ConsoleKey::RBS:
        emit rbsKeyDown();
        emit keyDown(Keyboard::Key::RBS);
        break;
    case ConsoleKey::RBP:
        emit rbpKeyDown();
        emit keyDown(Keyboard::Key::RBP);
        break;
    }
}

void CanKeyboard::consoleKeyReleased(ConsoleKey::ConsKey key)
{
    switch (key) {
    case ConsoleKey::BKSP:
    case ConsoleKey::L: // Установлено опытным путём
        emit backspaceKeyUp();
        emit keyUp(Keyboard::Key::BACKSPACE);
        break;
    case ConsoleKey::ENTER:
        emit enterKeyUp();
        emit keyUp(Keyboard::Key::ENTER);
        break;
    case ConsoleKey::OTM:
        emit cancelKeyUp();
        emit keyUp(Keyboard::Key::CANCEL);
        break;
    case ConsoleKey::K:
        emit commandKeyUp();
        emit keyUp(Keyboard::Key::COMMAND);
        break;
    case ConsoleKey::LGHT:
        emit brightnessKeyUp();
        emit keyUp(Keyboard::Key::BRIGHTNESS);
        break;
    case ConsoleKey::F0:
        emit numberKeyUp(0);
        emit keyUp(Keyboard::Key::K_0);
        break;
    case ConsoleKey::F1:
        emit numberKeyUp(1);
        emit keyUp(Keyboard::Key::K_1);
        break;
    case ConsoleKey::F2:
        emit numberKeyUp(2);
        emit keyUp(Keyboard::Key::K_2);
        break;
    case ConsoleKey::F3:
        emit numberKeyUp(3);
        emit keyUp(Keyboard::Key::K_3);
        break;
    case ConsoleKey::F4:
        emit numberKeyUp(4);
        emit keyUp(Keyboard::Key::K_4);
        break;
    case ConsoleKey::F5:
        emit numberKeyUp(5);
        emit keyUp(Keyboard::Key::K_5);
        break;
    case ConsoleKey::F6:
        emit numberKeyUp(6);
        emit keyUp(Keyboard::Key::K_6);
        break;
    case ConsoleKey::F7:
        emit numberKeyUp(7);
        emit keyUp(Keyboard::Key::K_7);
        break;
    case ConsoleKey::F8:
        emit numberKeyUp(8);
        emit keyUp(Keyboard::Key::K_8);
        break;
    case ConsoleKey::F9:
        emit numberKeyUp(9);
        emit keyUp(Keyboard::Key::K_9);
        break;
    case ConsoleKey::P:
        emit pKeyUp();
        emit keyUp(Keyboard::Key::P);
        break;
    case ConsoleKey::VK:
        emit vkKeyUp();
        emit keyUp(Keyboard::Key::VK);
        break;
    case ConsoleKey::RMP:
        emit rmpKeyUp();
        emit keyUp(Keyboard::Key::RMP);
        break;
    case ConsoleKey::F:
        emit fKeyUp();
        emit keyUp(Keyboard::Key::F);
        break;
    case ConsoleKey::TVK:
        emit tvkKeyUp();
        emit keyUp(Keyboard::Key::TVK);
        break;
    case ConsoleKey::K20:
        emit k20KeyUp();
        emit keyUp(Keyboard::Key::K20);
        break;
    case ConsoleKey::OC:
        emit ocKeyUp();
        emit keyUp(Keyboard::Key::OC);
        break;
    case ConsoleKey::OTPR:
        emit otprKeyUp();
        emit keyUp(Keyboard::Key::OTPR);
        break;
    case ConsoleKey::POD:
        emit podtKeyUp();
        emit keyUp(Keyboard::Key::PODT);
        break;
    case ConsoleKey::RB:
        emit rbKeyUp();
        emit keyUp(Keyboard::Key::RB);
        break;
    case ConsoleKey::RBS:
        emit rbsKeyUp();
        emit keyUp(Keyboard::Key::RBS);
        break;
    case ConsoleKey::RBP:
        emit rbpKeyUp();
        emit keyUp(Keyboard::Key::RBP);
        break;
    }
}



}
}
