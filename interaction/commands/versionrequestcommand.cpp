#include "versionrequestcommand.h"
#include "../contexts/versionrequestcontext.h"
#include "../activities/versionrequestactivity.h"
#include "../activities/popupactivity.h"

namespace Interaction {
namespace Commands {

VersionRequestCommand::VersionRequestCommand(int commandNumber,
                                             QString moduleName, SysDiagnostics::AuxModule moduleId, QVector<AuxResourceVersion *> auxResources,
                                             ICan *can, TextManager *textManager)
    : can (can), textManager (textManager), moduleName (moduleName), moduleId (moduleId), auxResources (auxResources), Command (commandNumber)
{ }

Story *VersionRequestCommand::createStory()
{
    auto context = new Contexts::VersionRequestContext ();
    Story *story = new Story(context, {
                                new Activities::VersionRequestActivity(moduleName, moduleId, auxResources, context, can, textManager),
                                new Activities::PopupActivity(&(context->versionString), 20000, textManager)
                             });
    return story;
}

}
}
