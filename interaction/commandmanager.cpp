#include "commandmanager.h"

namespace Interaction {

CommandManager::CommandManager(StoryManager *storyManager)
    : storyManager(storyManager)
{
}

bool CommandManager::ExecuteCommand(int commandId)
{
    for (int i = 0; i < commands.count(); i++)
    {
        if (commands[i].getId() == commandId)
        {
            // чё-каво вот тут вот с указателем?
            // кто когда чего удалит?
            storyManager->beginStory(*commands[i].getStory());
            break;
        }
    }
}

}
