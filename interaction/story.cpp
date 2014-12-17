#include "story.h"

namespace Interaction {

Story::Story(Context *storyContext, QList<Activities::Activity> activities)
    : context(storyContext), currentActivityIndex(-1), activities(activities)
{ }

void Story::SwitchNext()
{
    if (currentActivityIndex > 0)
        activities[currentActivityIndex].dispose();
    if (currentActivityIndex < activities.count())
    {
        currentActivityIndex++;
        activities[currentActivityIndex].run();
    }
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

}
