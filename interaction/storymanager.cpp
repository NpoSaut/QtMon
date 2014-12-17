#include "storymanager.h"

namespace Interaction {

StoryManager::StoryManager()
{
}

void StoryManager::beginStory(Story *story)
{
    if (currentStory != nullptr)
        closeCurrentStory();
    currentStory = story;
    currentStory->Begin();
}

void StoryManager::closeCurrentStory()
{
    currentStory->Dispose();
    delete currentStory;
}

}
