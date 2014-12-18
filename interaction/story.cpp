#include "story.h"

namespace Interaction {

Story::Story(Context *context, QVector<Activities::Activity *> activities, QObject *parent)
    : context (context), activities(activities), currentActivityIndex(-1),
      QObject(parent)
{ }

void Story::begin()
{
    if (currentActivityIndex == -1)
        switchNext();
}

void Story::switchNext()
{
    if (currentActivityIndex >= 0)
        disposeActivity();

    currentActivityIndex++;
    if (currentActivityIndex < activities.count())
        startActivity();
}

void Story::disposeActivity()
{
    disconnect(activities[currentActivityIndex], SIGNAL(completed()), this, SLOT(switchNext()));
    disconnect(activities[currentActivityIndex], SIGNAL(canselled()), this, SLOT(abort()));
    activities[currentActivityIndex]->dispose();
}

void Story::startActivity()
{
    connect(activities[currentActivityIndex], SIGNAL(completed()), this, SLOT(switchNext()));
    connect(activities[currentActivityIndex], SIGNAL(canselled()), this, SLOT(abort()));
    activities[currentActivityIndex]->run();
}

void Story::dispose()
{
    if (currentActivityIndex >= 0 && currentActivityIndex < activities.count())
        disposeActivity();
}

void Story::abort()
{
    if (currentActivityIndex >= 0 && currentActivityIndex < activities.count())
        disposeActivity();
}

Story::~Story()
{
    foreach (Activities::Activity *activity, activities) {
        delete activity;
    }
    if (context)
        delete context;
}

}
