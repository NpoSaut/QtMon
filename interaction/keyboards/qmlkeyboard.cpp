#include "qmlkeyboard.h"

namespace Interaction {
namespace Keyboards {

QmlKeyboard::QmlKeyboard(QObject *parent) :
    Keyboard(parent)
{
}


void QmlKeyboard::processKeyDown(int key)
{
    switch (key) {
    case Qt::Key_Backspace:
        emit backspaceKeyDown();
        emit keyDown(Key::BACKSPACE);
        break;
    case Qt::Key_Return:
        emit enterKeyDown();
        emit keyDown(Key::ENTER);
        break;
    case Qt::Key_Escape:
        emit cancelKeyDown();
        emit keyDown(Key::CANCEL);
        break;
    case Qt::Key_K:
        emit commandKeyDown();
        emit keyDown(Key::COMMAND);
        break;
    case Qt::Key_0:
        emit numberKeyDown(0);
        emit keyDown(Key::K_0);
        break;
    case Qt::Key_1:
        emit numberKeyDown(1);
        emit keyDown(Key::K_1);
        break;
    case Qt::Key_2:
        emit numberKeyDown(2);
        emit keyDown(Key::K_2);
        break;
    case Qt::Key_3:
        emit numberKeyDown(3);
        emit keyDown(Key::K_3);
        break;
    case Qt::Key_4:
        emit numberKeyDown(4);
        emit keyDown(Key::K_4);
        break;
    case Qt::Key_5:
        emit numberKeyDown(5);
        emit keyDown(Key::K_5);
        break;
    case Qt::Key_6:
        emit numberKeyDown(6);
        emit keyDown(Key::K_6);
        break;
    case Qt::Key_7:
        emit numberKeyDown(7);
        emit keyDown(Key::K_7);
        break;
    case Qt::Key_8:
        emit numberKeyDown(8);
        emit keyDown(Key::K_8);
        break;
    case Qt::Key_9:
        emit numberKeyDown(9);
        emit keyDown(Key::K_9);
        break;
    }
}

void QmlKeyboard::processKeyUp(int key)
{
    switch (key) {
    case Qt::Key_Backspace:
        emit backspaceKeyUp();
        emit keyUp(Key::BACKSPACE);
        break;
    case Qt::Key_Return:
        emit enterKeyUp();
        emit keyUp(Key::ENTER);
        break;
    case Qt::Key_Escape:
        emit cancelKeyUp();
        emit keyUp(Key::CANCEL);
        break;
    case Qt::Key_K:
        emit commandKeyUp();
        emit keyUp(Key::COMMAND);
        break;
    case Qt::Key_0:
        emit numberKeyUp(0);
        emit keyUp(Key::K_0);
        break;
    case Qt::Key_1:
        emit numberKeyUp(1);
        emit keyUp(Key::K_1);
        break;
    case Qt::Key_2:
        emit numberKeyUp(2);
        emit keyUp(Key::K_2);
        break;
    case Qt::Key_3:
        emit numberKeyUp(3);
        emit keyUp(Key::K_3);
        break;
    case Qt::Key_4:
        emit numberKeyUp(4);
        emit keyUp(Key::K_4);
        break;
    case Qt::Key_5:
        emit numberKeyUp(5);
        emit keyUp(Key::K_5);
        break;
    case Qt::Key_6:
        emit numberKeyUp(6);
        emit keyUp(Key::K_6);
        break;
    case Qt::Key_7:
        emit numberKeyUp(7);
        emit keyUp(Key::K_7);
        break;
    case Qt::Key_8:
        emit numberKeyUp(8);
        emit keyUp(Key::K_8);
        break;
    case Qt::Key_9:
        emit numberKeyUp(9);
        emit keyUp(Key::K_9);
        break;
    }
}

}
}
