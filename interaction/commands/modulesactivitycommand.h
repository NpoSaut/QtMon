#ifndef MODULESACTIVIYCOMMAND_H
#define MODULESACTIVIYCOMMAND_H

#include "../textmanager.h"
#include "../command.h"

namespace Interaction {
namespace Commands {

class ModulesActivityCommand : public Command
{
public:
    ModulesActivityCommand(TextManager *textManager);
    Story *createStory();

private:
    TextManager *textManager;
};

}
}

#endif // MODULESACTIVIYCOMMAND_H
