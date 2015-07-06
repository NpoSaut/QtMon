#include "keyboard.h"

#include <QMetaType>

namespace Interaction {

Keyboard::Keyboard(QObject *parent) :
    QObject(parent)
{
    qRegisterMetaType<Interaction::Keyboard::Key>("KeyboardKey");
}

}
