#include "keyboardmanager.h"

namespace Commands {

KeyboardManager::KeyboardManager(StoryManager *storyManager, QObject *parent)
    : storyManager (storyManager), QObject (parent)
{

}

void KeyboardManager::commandKeyPressed()
{
    Story s = new Story();

}

}
