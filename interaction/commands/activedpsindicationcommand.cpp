#include "activedpsindicationcommand.h"
#include "../activities/popupactivity.h"
#include <QString>

namespace Interaction {
namespace Commands {

ActiveDpsIndicationCommand::ActiveDpsIndicationCommand(IpdState *ipdSate, TextManager *textManager)
    : ipdState (ipdSate), textManager (textManager), Command (47)
{
}

Story *ActiveDpsIndicationCommand::createStory()
{
    return new Story (nullptr, { new Activities::PopupActivity( QString("Номер активного ДПС: %1").arg(ipdState->getActiveDpsNumber()), 10000, textManager) });
}

}
}
