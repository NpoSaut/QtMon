#ifndef STORYMANAGER_H
#define STORYMANAGER_H

#include <QObject>

#include "story.h"

namespace Interaction {

class StoryManager : public QObject
{
    Q_OBJECT
public:
    explicit StoryManager(QObject *parent = 0);

    void beginStory (Story *);

private:
    Story *currentStory;
};

}

#endif // STORYMANAGER_H
