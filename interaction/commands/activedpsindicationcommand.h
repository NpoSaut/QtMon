#ifndef ACTIVEDPSINDICATIONCOMMAND_H
#define ACTIVEDPSINDICATIONCOMMAND_H

#include "../textmanager.h"
#include "../command.h"
#include "qtBlokLib/parsers/ipd_state.h"

namespace Interaction {
namespace Commands {

class ActiveDpsIndicationCommand : public Command
{
public:
    ActiveDpsIndicationCommand(IpdState *ipdSate, TextManager *textManager);

    Story *createStory();

private:
    IpdState *ipdState;
    TextManager *textManager;
};

}
}

#endif // ACTIVEDPSINDICATIONCOMMAND_H
