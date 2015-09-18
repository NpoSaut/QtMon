#include "manualcoordinatecommand.h"
#include "../contexts/cookiescontext.h"
#include "../activities/inputactivity.h"
#include "../activities/ShiftedInputActivity.h"
#include "../activities/requestcookiesactivity.h"
#include "../activities/submitcookiesactivity.h"
#include "../activities/popupactivity.h"

namespace Interaction {
namespace Commands {

ManualcoordinateCommand::ManualcoordinateCommand(Cookies *cookies, TextManager *textManager)
    : cookies (cookies), textManager (textManager), Command (6)
{
}

Story *ManualcoordinateCommand::createStory()
{
    auto *context = new Contexts::CookiesContext({
                                {&cookies->startOrdinate, "Координата: %1"},
                                {&cookies->ordinateIncreaseDirection, "Направление: %1 (0 - назад, 1 - вперёд}"},
                                                   });

    QVector<Activities::Activity *> activities;
    activities.append(new Activities::RequestCookiesActivity(context, textManager));
    activities.append(new Activities::ShiftedInputActivity(context->records[0].text, &(context->records[0].value), 1100, textManager));
    activities.append(new Activities::InputActivity(context->records[1].text, &(context->records[1].value), textManager));
    activities.append(new Activities::InputActivity("Нажмите ВВОД для подтверждения записи", nullptr, textManager));
    activities.append(new Activities::SubmitCookiesActivity(context, textManager));
    activities.append(new Activities::PopupActivity(&(context->resultMessage), 5000, textManager));

    return new Story(context, activities);
}

}
}
