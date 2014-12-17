#ifndef STORYMANAGER_H
#define STORYMANAGER_H

#include "story.h"

namespace Interaction {

class StoryManager
{
public:
    explicit StoryManager();

    void beginStory (Story *story);

private:
    Story *currentStory;
    void closeCurrentStory();
};

}

#endif // STORYMANAGER_H
