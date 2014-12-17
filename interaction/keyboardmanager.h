#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H

#include <QObject>

#include "storymanager.h"
#include "textmanager.h"
#include "commandmanager.h"

namespace Interaction {

class KeyboardManager : public QObject
{
    Q_OBJECT
public:
    explicit KeyboardManager(StoryManager *storyManager, CommandManager *commandsManager, TextManager *textManager, QObject *parent = 0);

public slots:
    void commandKeyPressed ();
    void cancelKeyPressed ();

private:
    CommandManager *commandsManager;
    StoryManager *storyManager;
    TextManager *textManager;
};

}

#endif // KEYBOARDMANAGER_H
