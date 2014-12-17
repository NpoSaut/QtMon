#include "keyboardmanager.h"
#include "activities/inputparameteractivity.h"
#include "contexts/executecommandcontext.h"

namespace Commands {

KeyboardManager::KeyboardManager(StoryManager *storyManager, TextManager *textManager, QObject *parent)
    : storyManager (storyManager), textManager(textManager), QObject (parent)
{

}

void KeyboardManager::commandKeyPressed()
{
    ExecuteCommandContext* context = new ExecuteCommandContext();
    Story s = new Story();
    s.append(new Activities::InputParameterActivity("Номер команды: %1", context->commandNumber*, TextManager));
}

}
