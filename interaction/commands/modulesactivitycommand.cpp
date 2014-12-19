#include "modulesactivitycommand.h"
#include "../activities/awaitmodulesactivityactivity.h"
#include "../activities/displaymodulesactivityactivity.h"

namespace Interaction {
namespace Commands {

ModulesActivityCommand::ModulesActivityCommand(McoState *mcoState, TextManager *textManager)
    : mcoState(mcoState), textManager (textManager), Command (71)
{
}

Story *ModulesActivityCommand::createStory()
{
    auto *context = new Contexts::ModulesActivityContext ();
    Story *story = new Story(context, {
                                 new Activities::AwaitModulesActivityActivity(context, mcoState, textManager),
                                 new Activities::DisplayModulesActivityActivity(context, textManager)
                             });
    return story;
}

}
}
