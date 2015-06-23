#ifndef CONFIGURECOMMAND_H
#define CONFIGURECOMMAND_H

#include "../textmanager.h"
#include "../command.h"
#include "qtBlokLib/cookies.h"

namespace Interaction {
namespace Commands {

class ConfigureCommand : public Command
{
public:
    ConfigureCommand(Cookies *cookies, TextManager *textManager);
    Story *createStory();

private:
    Cookies *cookies;
    TextManager *textManager;
};

}
}

#endif // CONFIGURECOMMAND_H
