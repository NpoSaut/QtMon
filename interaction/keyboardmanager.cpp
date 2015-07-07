#include "keyboardmanager.h"
#include "activities/inputactivity.h"
#include "activities/executecommandactivity.h"
#include "contexts/executecommandcontext.h"

namespace Interaction {

KeyboardManager::KeyboardManager(Keyboard *keyboard, StoryManager *storyManager, CommandManager *commandsManager, TextManager *textManager, QMap<Keyboard::Key, Command*> *hotkeys, QObject *parent)
    : keyboard (keyboard), storyManager (storyManager), commandsManager (commandsManager), textManager(textManager), hotkeys(hotkeys),
      QObject (parent)
{
    connect (keyboard, SIGNAL(commandKeyDown()), this, SLOT(commandKeyPressed()));
    connect (keyboard, SIGNAL(cancelKeyDown()), this, SLOT(cancelKeyPressed()));
    connect (keyboard, SIGNAL(keyDown(Interaction::Keyboard::Key)), this, SLOT(anyKeyPressed(Interaction::Keyboard::Key)));
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

void KeyboardManager::anyKeyPressed(Keyboard::Key key)
{
    if (hotkeys->contains(key))
    {
        Command *command = (*hotkeys)[key];
        Story *story = command->createStory();
        storyManager->beginStory(story);
    }
}

}
