#ifndef CANKEYBOARD_H
#define CANKEYBOARD_H

#include "../keyboard.h"
#include "qtBlokLib/parsers/console_key.h"

namespace Interaction {
namespace Keyboards {

class CanKeyboard : public Keyboard
{
    Q_OBJECT
public:
    explicit CanKeyboard(ConsoleKey *consoleKey, QObject *parent = 0);

signals:
    void keyDown (Key);
    void keyUp (Key);

    void numberKeyDown (int);
    void numberKeyUp (int);

    void backspaceKeyDown ();
    void backspaceKeyUp ();
    void enterKeyDown ();
    void enterKeyUp ();
    void cancelKeyDown ();
    void cancelKeyUp ();
    void commandKeyDown ();
    void commandKeyUp ();

private slots:
    void consoleKeyPressed (ConsoleKey::ConsKey key);
    void consoleKeyReleased (ConsoleKey::ConsKey key);

private:
    ConsoleKey *consoleKey;
};

}
}

#endif // CANKEYBOARD_H
