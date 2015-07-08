#ifndef CHANGEBRIGHTNESSCOMMAND_H
#define CHANGEBRIGHTNESSCOMMAND_H

#include "../textmanager.h"
#include "../command.h"
#include "illumination/interfaces/IIlluminationManager.h"

namespace Interaction {
namespace Commands {

class ChangeBrightnessCommand : public Command
{
public:
    ChangeBrightnessCommand(IIlluminationManager *illuminationManager, TextManager *textManager);
    Story *createStory();

private:
    IIlluminationManager *illuminationManager;
    TextManager *textManager;

};

}
}

#endif // CHANGEBRIGHTNESSCOMMAND_H
