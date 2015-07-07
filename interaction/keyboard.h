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
        BRIGHTNESS = 14,
        P = 15,
        VK = 16,
        RMP = 17,
        F = 18,
        K20 = 20,
        OC = 21,
        OTPR = 22,
        PODT = 23,
        RB = 24,
        RBS = 25,
        RBP = 26
    };

signals:
    void keyDown (Interaction::Keyboard::Key);
    void keyUp (Interaction::Keyboard::Key);

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
    void pKeyUp ();
    void pKeyDown ();
    void vkKeyUp ();
    void vkKeyDown ();
    void rmpKeyUp ();
    void rmpKeyDown ();
    void fKeyUp ();
    void fKeyDown ();
    void k20KeyUp ();
    void k20KeyDown ();
    void ocKeyUp ();
    void ocKeyDown ();
    void otprKeyUp ();
    void otprKeyDown ();
    void podtKeyUp ();
    void podtKeyDown ();
    void rbKeyDown ();
    void rbKeyUp ();
    void rbsKeyDown ();
    void rbsKeyUp ();
    void rbpKeyDown ();
    void rbpKeyUp ();
};

}

#endif // KEYBOARD_H
