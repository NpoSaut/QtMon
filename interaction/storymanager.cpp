#include "storymanager.h"

namespace Interaction {

StoryManager::StoryManager()
    : currentStory (nullptr)
{ }

void StoryManager::beginStory(Story *story)
{
    closeCurrentStory();
    currentStory = story;
    currentStory->begin();
}

void StoryManager::closeCurrentStory()
{
    if (currentStory != nullptr)
    {
        currentStory->dispose();
        delete currentStory;
    }
}

}
