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
    if (currentActivityIndex > 0)
        disposeCurrent();

    if (currentActivityIndex < activities.count())
        startNext();
}

void Story::disposeCurrent()
{
    disconnect(activities[currentActivityIndex], SIGNAL(completed), this, SLOT(switchNext()));
    disconnect(activities[currentActivityIndex], SIGNAL(canselled), this, SLOT(abort()));
    activities[currentActivityIndex]->dispose();
}

void Story::startNext()
{
    currentActivityIndex++;
    connect(activities[currentActivityIndex], SIGNAL(completed), this, SLOT(switchNext()));
    connect(activities[currentActivityIndex], SIGNAL(canselled), this, SLOT(abort()));
    activities[currentActivityIndex]->run();
}

void Story::dispose()
{
    disposeCurrent();
}

void Story::abort()
{
    disposeCurrent();
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
