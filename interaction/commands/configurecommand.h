#ifndef CONFIGURECOMMAND_H
#define CONFIGURECOMMAND_H

#include "../textmanager.h"
#include "../command.h"

namespace Interaction {
namespace Commands {

class ConfigureCommand : public Command
{
public:
    ConfigureCommand(TextManager *textManager);
    Story getStory();

private:
    TextManager *textManager;

};

}
}

#endif // CONFIGURECOMMAND_H
