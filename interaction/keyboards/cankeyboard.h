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

private slots:
    void consoleKeyPressed (ConsoleKey::ConsKey key);
    void consoleKeyReleased (ConsoleKey::ConsKey key);

private:
    ConsoleKey *consoleKey;
};

}
}

#endif // CANKEYBOARD_H
