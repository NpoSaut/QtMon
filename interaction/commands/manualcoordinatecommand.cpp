#include "manualcoordinatecommand.h"
#include "../contexts/cookiescontext.h"
#include "../activities/inputactivity.h"
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
    for (int i = 0; i < context->records.count(); i ++)
        activities.append(new Activities::InputActivity(
                              context->records[i].text,
                              &(context->records[i].value),
                              textManager));
    activities.append(new Activities::InputActivity("Нажмите ВВОД для подтверждения записи", nullptr, textManager));
    activities.append(new Activities::SubmitCookiesActivity(context, textManager));
    activities.append(new Activities::PopupActivity(&(context->resultMessage), 5000, textManager));

    return new Story(context, activities);
}

}
}
