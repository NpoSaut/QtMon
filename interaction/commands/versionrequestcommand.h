#ifndef VERSIONREQUESTCOMMAND_H
#define VERSIONREQUESTCOMMAND_H

#include <QString>
#include <QVector>
#include "../command.h"
#include "../textmanager.h"
#include "qtCanLib/can.h"
#include "qtBlokLib/parsers/sys_diagnostics.h"
#include "qtBlokLib/parsers/aux_resource.h"

namespace Interaction {
namespace Commands {

class VersionRequestCommand : public Command
{
public:
    VersionRequestCommand(int commandNumber,
                          QString moduleName, SysDiagnostics::AuxModule moduleId, QVector<AuxResourceVersion *> auxResources,
                          Can *can, TextManager *textManager);

    Story *createStory();

private:
    Can *can;
    TextManager *textManager;

    QString moduleName;
    SysDiagnostics::AuxModule moduleId;
    QVector<AuxResourceVersion *> auxResources;
};

}
}

#endif // VERSIONREQUESTCOMMAND_H
