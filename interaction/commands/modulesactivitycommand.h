#ifndef MODULESACTIVIYCOMMAND_H
#define MODULESACTIVIYCOMMAND_H

#include "../textmanager.h"
#include "../command.h"
#include "qtBlokLib/parsers/mco_state.h"

namespace Interaction {
namespace Commands {

class ModulesActivityCommand : public Command
{
public:
    ModulesActivityCommand(McoState *mcoState, TextManager *textManager);
    Story *createStory();

private:
    McoState *mcoState;
    TextManager *textManager;
};

}
}

#endif // MODULESACTIVIYCOMMAND_H
