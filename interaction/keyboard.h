#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QObject>

namespace Interaction {

class Keyboard : public QObject
{
    Q_OBJECT
public:
    explicit Keyboard(QObject *parent = 0);

    enum Key {
        K_0 = 0,
        K_1 = 1,
        K_2 = 2,
        K_3 = 3,
        K_4 = 4,
        K_5 = 5,
        K_6 = 6,
        K_7 = 7,
        K_8 = 8,
        K_9 = 9,
        BACKSPACE = 10,
        ENTER = 11,
        CANCEL = 12,
        COMMAND = 13,
        BRIGHTNESS = 14
    };

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
    void brightnessKeyDown ();
    void brightnessKeyUp ();
};

}

#endif // KEYBOARD_H
