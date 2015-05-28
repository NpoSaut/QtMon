#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H

#include <QObject>

#include "storymanager.h"
#include "textmanager.h"
#include "commandmanager.h"
#include "keyboard.h"

#include "illumination/interfaces/IIlluminationManager.h"

namespace Interaction {

class KeyboardManager : public QObject
{
    Q_OBJECT
public:
    explicit KeyboardManager(Keyboard *keyboard, StoryManager *storyManager, CommandManager *commandsManager, TextManager *textManager, IIlluminationManager *illumonationManager, QObject *parent = 0);

private slots:
    void commandKeyPressed ();
    void brightnessKeyPressed ();
    void cancelKeyPressed ();

private:
    Keyboard *keyboard;
    StoryManager *storyManager;
    CommandManager *commandsManager;
    TextManager *textManager;
    IIlluminationManager *illumonationManager;
};

}

#endif // KEYBOARDMANAGER_H
