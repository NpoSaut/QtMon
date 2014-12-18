#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <QVector>
#include "command.h"
#include "storymanager.h"

namespace Interaction {

// Хранит команды и запускает нужную по номеру
class CommandManager
{
public:
    CommandManager(StoryManager *storyManager);
    bool executeCommand(int commandId);

private:
    StoryManager *storyManager;
    QVector<Command *> commands;
};

}

#endif // COMMANDMANAGER_H
