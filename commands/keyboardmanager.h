#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H

#include <QObject>

#include "storymanager.h"

namespace Commands {

class KeyboardManager : public QObject
{
    Q_OBJECT
public:
    explicit KeyboardManager(StoryManager *storyManager, QObject *parent = 0);

public slots:
    void commandKeyPressed ();
    void cancelKeyPressed ();

private:
    StoryManager *storyManager;
};

}

#endif // KEYBOARDMANAGER_H
