#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H

#include <QObject>

#include "storymanager.h"
#include "textmanager.h"
#include "commandmanager.h"
#include "keyboard.h"

namespace Interaction {

class KeyboardManager : public QObject
{
    Q_OBJECT
public:
    explicit KeyboardManager(Keyboard *keyboard, StoryManager *storyManager, CommandManager *commandsManager, TextManager *textManager, QObject *parent = 0);

private slots:
    void commandKeyPressed ();
    void cancelKeyPressed ();

private:
    Keyboard *keyboard;
    StoryManager *storyManager;
    CommandManager *commandsManager;
    TextManager *textManager;
};

}

#endif // KEYBOARDMANAGER_H
