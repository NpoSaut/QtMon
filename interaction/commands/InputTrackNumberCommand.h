#ifndef INPUTTRACKNUMBERCOMMAND_H
#define INPUTTRACKNUMBERCOMMAND_H

#include "../textmanager.h"
#include "../command.h"
#include "qtBlokLib/cookies.h"

namespace Interaction {
namespace Commands {

class InputTrackNumberCommand : public Command
{
public:
    InputTrackNumberCommand(Cookies *cookies, TextManager *textManager);
    Story *createStory();

private:
    Cookies *cookies;
    TextManager *textManager;

};

}
}

#endif // INPUTTRACKNUMBERCOMMAND_H
