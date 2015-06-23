#ifndef MANUALCOORDINATECOMMAND_H
#define MANUALCOORDINATECOMMAND_H

#include "../textmanager.h"
#include "../command.h"
#include "qtBlokLib/cookies.h"

namespace Interaction {
namespace Commands {

class ManualcoordinateCommand : public Command
{
public:
    ManualcoordinateCommand(Cookies *cookies, TextManager *textManager);
    Story *createStory();

private:
    Cookies *cookies;
    TextManager *textManager;
};

}
}


#endif // MANUALCOORDINATECOMMAND_H
