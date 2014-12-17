#include "story.h"

namespace Interaction {

Story::Story(Context *storyContext, QList<Activities::Activity> activities, QObject *parent)
    : context(storyContext), currentActivityIndex(-1), activities(activities),
      QObject(parent)
{ }

void Story::Begin()
{
    if (currentActivityIndex != -1) return;
    SwitchNext();
}

void Story::SwitchNext()
{
    if (currentActivityIndex > 0)
        DisposeCurrent();

    if (currentActivityIndex < activities.count())
        StartNext();
}

void Story::DisposeCurrent()
{
    disconnect(*activities[currentActivityIndex], SIGNAL(completed), this, SLOT(SwitchNext()));
    dicconnect(*activities[currentActivityIndex], SIGNAL(canselled), this, SLOT(Abort()));
    activities[currentActivityIndex].dispose();
}

void Story::StartNext()
{
    currentActivityIndex++;
    connect(*activities[currentActivityIndex], SIGNAL(completed), this, SLOT(SwitchNext()));
    connect(*activities[currentActivityIndex], SIGNAL(canselled), this, SLOT(Abort()));
    activities[currentActivityIndex].run();
}

void Story::Dispose()
{
    for (int i = currentActivityIndex; i < activities.count(); i++)
    {
        // вроде как, мы принмаем этот список как копию,
        // поэтому можно не удалять из него ничего, да?
        activities[i].dispose();
    }
    if (context != nullptr)
        delete context;
}

void Story::Abort()
{
    DisposeCurrent();
}

}
