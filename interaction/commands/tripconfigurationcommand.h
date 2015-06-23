#ifndef TRIPCONFIGURATIONCOMMAND_H
#define TRIPCONFIGURATIONCOMMAND_H

#include "../textmanager.h"
#include "../command.h"
#include "qtBlokLib/cookies.h"

namespace Interaction {
namespace Commands {

class TripConfigurationCommand : public Command
{
public:
    TripConfigurationCommand(Cookies *cookies, TextManager *textManager);
    Story *createStory();

private:
    Cookies *cookies;
    TextManager *textManager;
};

}
}

#endif // TRIPCONFIGURATIONCOMMAND_H
