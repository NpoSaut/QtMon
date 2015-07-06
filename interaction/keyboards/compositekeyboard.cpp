#include "compositekeyboard.h"

#include <QMetaObject>
#include <QMetaMethod>

namespace Interaction {
namespace Keyboards {

CompositeKeyboard::CompositeKeyboard(QVector<Keyboard *> keyboards, QObject *parent) :
    Keyboard(parent)
{
    foreach (Keyboard *keyboard, keyboards) {
        for (int i = 0; i < keyboard->metaObject()->methodCount(); i++) {
            QMetaMethod method = keyboard->metaObject()->method(i);
            if ( method.methodType() == QMetaMethod::Signal ) {
                connect (keyboard, method, this, method);
            }
        }
    }
}

}
}
