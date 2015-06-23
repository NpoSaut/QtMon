#ifndef STORYMANAGER_H
#define STORYMANAGER_H

#include "story.h"

namespace Interaction {

// Запускает, хранит и удаляет текущую историю
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
