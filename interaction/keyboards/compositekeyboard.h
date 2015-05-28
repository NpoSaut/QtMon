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

private slots:
    void onKeyDown (Key key);
    void onKeyUp (Key key);

    void onNumberKeyDown (int d);
    void onNumberKeyUp (int d);

    void onBackspaceKeyDown ();
    void onBackspaceKeyUp ();
    void onEnterKeyDown ();
    void onEnterKeyUp ();
    void onCancelKeyDown ();
    void onCancelKeyUp ();
    void onCommandKeyDown ();
    void onCommandKeyUp ();
    void onBrightnessKeyDown ();
    void onBrightnessKeyUp ();
};

}
}

#endif // COMPOSITEKEYBOARD_H
