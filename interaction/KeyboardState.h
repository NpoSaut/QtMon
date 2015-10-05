#ifndef KEYBOARDSTATE_H
#define KEYBOARDSTATE_H

#include <QObject>
#include <QVector>

#include "keyboard.h"

namespace Interaction {

class KeyboardState : public QObject
{
    Q_OBJECT
public:
    explicit KeyboardState(Keyboard *keyboard, QObject *parent = 0);

    bool isPressed (Keyboard::Key key);

signals:
    void stateChanged ();

private slots:
    void keyDown (Interaction::Keyboard::Key key);
    void keyUp (Interaction::Keyboard::Key key);

private:
    QVector<Keyboard::Key> pressedKeys;
};

}

#endif // KEYBOARDSTATE_H
