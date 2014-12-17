#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <QList>
#include "command.h"
#include"storymanager.h"

namespace Interaction {

class CommandManager
{
public:
    CommandManager(StoryManager *storyManager);
    bool ExecuteCommand(int commandId);

private:
    StoryManager *storyManager;
    QList<Command> commands;
};

}

#endif // COMMANDMANAGER_H
