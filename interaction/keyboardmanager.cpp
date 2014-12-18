#include "keyboardmanager.h"
#include "activities/inputparameteractivity.h"
#include "activities/executecommandactivity.h"
#include "contexts/executecommandcontext.h"

namespace Interaction {

KeyboardManager::KeyboardManager(StoryManager *storyManager, CommandManager *commandsManager, TextManager *textManager, QObject *parent)
    : storyManager (storyManager), commandsManager (commandsManager), textManager(textManager),
      QObject (parent)
{

}

void KeyboardManager::commandKeyPressed()
{
    auto *context = new Contexts::ExecuteCommandContext();
    Story *s = new Story(context, {
                            new Activities::InputParameterActivity("Номер команды: %1", &context->commandNumber, textManager),
                            new Activities::ExecuteCommandActivity(context, commandsManager)
                        });
    storyManager->beginStory(s);
}

void KeyboardManager::cancelKeyPressed()
{

}

}
