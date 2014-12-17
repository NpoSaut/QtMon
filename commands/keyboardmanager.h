#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H

#include <QObject>

#include "storymanager.h"
#include "textmanager.h"

namespace Commands {

class KeyboardManager : public QObject
{
    Q_OBJECT
public:
    explicit KeyboardManager(StoryManager *storyManager, TextManager *textManager, QObject *parent = 0);

public slots:
    void commandKeyPressed ();
    void cancelKeyPressed ();

private:
    StoryManager *storyManager;
    TextManager *textManager;
};

}

#endif // KEYBOARDMANAGER_H
