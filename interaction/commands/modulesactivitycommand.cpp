#include "modulesactivitycommand.h"
#include "../activities/displaymodulesactivityactivity.h"

namespace Interaction {
namespace Commands {

ModulesActivityCommand::ModulesActivityCommand(McoState *mcoState, TextManager *textManager)
    : mcoState(mcoState), textManager (textManager), Command (71)
{
}

Story *ModulesActivityCommand::createStory()
{
    Story *story = new Story(nullptr, {
                                 new Activities::DisplayModulesActivityActivity(mcoState, textManager)
                             });
    return story;
}

}
}
