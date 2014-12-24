#include "TripConfigurationCommand.h"
#include "../contexts/cookiescontext.h"
#include "../activities/inputactivity.h"
#include "../activities/requestcookiesactivity.h"
#include "../activities/submitcookiesactivity.h"
#include "../activities/popupactivity.h"

namespace Interaction {
namespace Commands {

TripConfigurationCommand::TripConfigurationCommand(Cookies *cookies, TextManager *textManager)
    : cookies (cookies), textManager (textManager), Command (7)
{
}

Story *TripConfigurationCommand::createStory()
{
    auto *context = new Contexts::CookiesContext({
                                {&cookies->machinistNumber, "Номер машиниста: %1"},
                                {&cookies->trainNumber, "Номер поезда: %1"},
                                {&cookies->lengthInWheels, "Длина поезда: %1 осей"},
                                {&cookies->lengthInWagons, "Длина поезда: %1 вагонов"},
                                {&cookies->mass, "Масса поезда: %1 тонн"},
                                                   },
                                                 "Счастливого пути!");

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
