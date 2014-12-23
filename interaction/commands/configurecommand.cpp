#include "configurecommand.h"
#include "../contexts/cookiescontext.h"
#include "../activities/inputactivity.h"
#include "../activities/requestcookiesactivity.h"
#include "../activities/submitcookiesactivity.h"

namespace Interaction {
namespace Commands {

ConfigureCommand::ConfigureCommand(Cookies *cookies, TextManager *textManager)
    : cookies (cookies), textManager (textManager), Command (5)
{
}

Story *ConfigureCommand::createStory()
{
    auto *context = new Contexts::CookiesContext({
                                {&cookies->categoryTrain, "Категория поезда: %1"},
                                {&cookies->timeshift, "Время: %1 (0 - зимнее, 1 - летнее}"},
                                {&cookies->locomotiveKind, "Тип локомотива: %1"},
                                {&cookies->locomotiveNumber, "Номер локомотива: %1"},
                                {&cookies->diameter1, "Диаметр бандажа колеса 1: %1 мм"},
                                {&cookies->diameter2, "Диаметр бандажа колеса 2: %1 мм"},
                                {&cookies->dpsDentos, "Число зубьев ДС: %1"},
                                {&cookies->configuration, "Конфигурация: %1"},
                                {&cookies->speedLimitWhite, "Скорость на \"Белый\": %1 км/ч"},
                                {&cookies->speedLimitRedYellow, "Скорость на \"Жёлтый\": %1 км/ч"},
                                {&cookies->speedLimitGreen, "Скорость на \"Зелёный\": %1 км/ч"},
                                {&cookies->dozorLength, "Длина блок-участка: %1 м"},
                                                   });

    QVector<Activities::Activity *> activities;
    activities.append(new Activities::RequestCookiesActivity(context, textManager));
    for (int i = 0; i < context->records.count(); i ++)
        activities.append(new Activities::InputActivity(
                              context->records[i].text,
                              &(context->records[i].value),
                              textManager));
    activities.append(new Activities::SubmitCookiesActivity(context, textManager));

    return new Story(context, activities);
}

}
}
