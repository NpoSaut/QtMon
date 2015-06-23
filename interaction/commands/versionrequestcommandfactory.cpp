#include "versionrequestcommandfactory.h"

namespace Interaction {
namespace Commands {

VersionRequestCommandFactory::VersionRequestCommandFactory(Can *can, Parser *parser, TextManager *textManager)
    : can (can), parser (parser), textManager (textManager)
{
}

VersionRequestCommand *VersionRequestCommandFactory::produceCommand(int commandNumber, QString moduleName, SysDiagnostics::AuxModule moduleId, QVector<AuxResource::Descriptor> descriptors)
{
    QVector<AuxResourceVersion *> auxResources (descriptors.count());
    for (int i = 0; i < auxResources.count(); i ++)
        auxResources[i] = parser->auxResources[descriptors[i]];

    return new VersionRequestCommand (commandNumber, moduleName, moduleId, auxResources, can, textManager);
}

}
}
