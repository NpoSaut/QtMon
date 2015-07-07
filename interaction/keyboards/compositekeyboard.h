#ifndef COMPOSITEKEYBOARD_H
#define COMPOSITEKEYBOARD_H

#include <QVector>
#include "../keyboard.h"

namespace Interaction {
namespace Keyboards {

class CompositeKeyboard : public Keyboard
{
    Q_OBJECT
public:
    explicit CompositeKeyboard(QVector<Keyboard *> keyboards, QObject *parent = 0);
};

}
}

#endif // COMPOSITEKEYBOARD_H
