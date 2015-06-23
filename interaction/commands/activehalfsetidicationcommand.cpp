#include "activehalfsetidicationcommand.h"
#include "../activities/popupactivity.h"
#include <QString>

namespace Interaction {
namespace Commands {

ActiveHalfsetIdicationCommand::ActiveHalfsetIdicationCommand(McoState *mcoState, TextManager *textManager)
    : mcoState (mcoState), textManager (textManager), Command (46)
{
}

Story *ActiveHalfsetIdicationCommand::createStory()
{
    return new Story (nullptr, { new Activities::PopupActivity( QString("Номер активного комлекта: %1").arg(mcoState->getActiveHalfset()), 10000, textManager) });
}

}
}
