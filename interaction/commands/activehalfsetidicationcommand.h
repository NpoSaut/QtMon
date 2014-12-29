#ifndef ACTIVEHALFSETIDICATIONCOMMAND_H
#define ACTIVEHALFSETIDICATIONCOMMAND_H

#include "../textmanager.h"
#include "../command.h"
#include "qtBlokLib/parsers/mco_state.h"

namespace Interaction {
namespace Commands {

class ActiveHalfsetIdicationCommand : public Command
{
public:
    ActiveHalfsetIdicationCommand(McoState *mcoState, TextManager *textManager);

    Story *createStory();

private:
    McoState *mcoState;
    TextManager *textManager;
};

}
}

#endif // ACTIVEHALFSETIDICATIONCOMMAND_H
