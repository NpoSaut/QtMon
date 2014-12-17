#include "keyboardmanager.h"
#include "activities/inputparameteractivity.h"
#include "activities/executecommandactivity.h"
#include "contexts/executecommandcontext.h"

namespace Interaction {

KeyboardManager::KeyboardManager(StoryManager *storyManager, CommandManager *commandsManager, TextManager *textManager, QObject *parent)
    : storyManager (storyManager), textManager(textManager), commandsManager (commandsManager),
      QObject (parent)
{

}

void KeyboardManager::commandKeyPressed()
{
    ExecuteCommandContext* context = new ExecuteCommandContext();
    Story s = new Story(context);
    s.append(new Activities::InputParameterActivity("Номер команды: %1", context->commandNumber*, TextManager));
    s.append(new Activities::ExecuteCommandActivity(context, commandsManager));
}

}
