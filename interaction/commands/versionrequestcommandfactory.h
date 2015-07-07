#ifndef VERSIONREQUESTCOMMANDFACTORY_H
#define VERSIONREQUESTCOMMANDFACTORY_H

#include "../textmanager.h"
#include "qtCanLib/ICan.h"
#include "qtBlokLib/parser.h"
#include "versionrequestcommand.h"

namespace Interaction {
namespace Commands {

class VersionRequestCommandFactory
{
public:
    VersionRequestCommandFactory(ICan *can, Parser *parser, TextManager *textManager);

    VersionRequestCommand *produceCommand (int commandNumber, QString moduleName, SysDiagnostics::AuxModule moduleId, QVector<AuxResource::Descriptor> descriptors);

private:
    ICan *can;
    Parser *parser;
    TextManager *textManager;
};

}
}

#endif // VERSIONREQUESTCOMMANDFACTORY_H
