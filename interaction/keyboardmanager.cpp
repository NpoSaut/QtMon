#include "keyboardmanager.h"
#include "activities/inputactivity.h"
#include "activities/executecommandactivity.h"
#include "contexts/executecommandcontext.h"

namespace Interaction {

KeyboardManager::KeyboardManager(Keyboard *keyboard, StoryManager *storyManager, CommandManager *commandsManager, TextManager *textManager, QObject *parent)
    : keyboard (keyboard), storyManager (storyManager), commandsManager (commandsManager), textManager(textManager),
      QObject (parent)
{
    connect (keyboard, SIGNAL(commandKeyDown()), this, SLOT(commandKeyPressed()));
    connect (keyboard, SIGNAL(cancelKeyDown()), this, SLOT(cancelKeyPressed()));
}

void KeyboardManager::commandKeyPressed()
{
    auto *context = new Contexts::ExecuteCommandContext();
    Story *s = new Story(context, {
                            new Activities::InputActivity("Номер команды: %1", &context->commandNumber, textManager),
                            new Activities::ExecuteCommandActivity(context, commandsManager)
                        });
    storyManager->beginStory(s);
}

void KeyboardManager::cancelKeyPressed()
{
    storyManager->beginStory(new Story(nullptr, QVector<Activities::Activity *> (0)));
}

}
