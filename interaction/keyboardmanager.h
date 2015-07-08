#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H

#include <QObject>
#include <QMap>

#include "storymanager.h"
#include "textmanager.h"
#include "commandmanager.h"
#include "keyboard.h"

namespace Interaction {

class KeyboardManager : public QObject
{
    Q_OBJECT
public:
    explicit KeyboardManager(Keyboard *keyboard, StoryManager *storyManager, CommandManager *commandsManager, TextManager *textManager, QMap<Keyboard::Key, Command*> *hotkeys, QObject *parent = 0);

private slots:
    void commandKeyPressed ();
    void cancelKeyPressed ();
    void anyKeyPressed (Interaction::Keyboard::Key key);

private:
    Keyboard *keyboard;
    StoryManager *storyManager;
    CommandManager *commandsManager;
    TextManager *textManager;

    QMap<Keyboard::Key, Command*> *hotkeys;

};

}

#endif // KEYBOARDMANAGER_H
