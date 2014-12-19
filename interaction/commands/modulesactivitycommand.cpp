#include "modulesactivitycommand.h"
#include "../activities/modulesactivityactivity.h"

namespace Interaction {
namespace Commands {

ModulesActivityCommand::ModulesActivityCommand(TextManager *textManager)
    : textManager (textManager), Command (71)
{
}

Story *ModulesActivityCommand::createStory()
{
    Story *story = new Story(nullptr, {
                                new Activities::ModulesActivityActivity(textManager),
                             });
    return story;
}

}
}
