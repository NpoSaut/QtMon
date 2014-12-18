#ifndef QMLKEYBOARD_H
#define QMLKEYBOARD_H

#include "../keyboard.h"

namespace Interaction {
namespace Keyboards {

class QmlKeyboard : public Keyboard
{
    Q_OBJECT
public:
    explicit QmlKeyboard(QObject *parent = 0);
    void processKeyDowm(int key);
    void processKeyUp(int key);

signals:

public slots:

};

}
}

#endif // QMLKEYBOARD_H
