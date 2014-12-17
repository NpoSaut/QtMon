#include "configurecommand.h"
#include "../contexts/configurecontext.h"
#include "../activities/inputparameteractivity.h"
#include "../activities/requestconfigurationactivity.h"
#include "../activities/submitconfigurationactivity.h"

namespace Interaction {
namespace Commands {

ConfigureCommand::ConfigureCommand(TextManager *textManager)
    : textManager (textManager)
{
}

Story ConfigureCommand::getStory()
{
    ConfigureContext *context = new ConfigureContext();
    Story story(context);
    story.append(new Activities::RequestConfigurationActivity(context, textManager));
    story.append(new Activities::InputParameterActivity("Категория поезда: %1", context->trainCategory, textManager));
    story.append(new Activities::InputParameterActivity("Время: %1 (0 - зимнее, 1 - летнее)", context->summerTime, textManager));
    story.append(new Activities::InputParameterActivity("Тип локомотива: %1", context->locomotiveKind, textManager));
    story.append(new Activities::InputParameterActivity("Номер локомотива: %1", context->locomotiveNumber, textManager));
    story.append(new Activities::InputParameterActivity("Диаметр бандажа колеса 1: %1 мм", context->diameter1, textManager));
    story.append(new Activities::InputParameterActivity("Диаметр бандажа колеса 2: %1 мм", context->diameter2, textManager));
    story.append(new Activities::InputParameterActivity("Число зубьев ДС: %1", context->impulsesPerCycle, textManager));
    story.append(new Activities::InputParameterActivity("Конфигурация: %1", context->configuration, textManager));
    story.append(new Activities::InputParameterActivity("Скорость на \"Белый\": %1 км/ч", context->speedWhite, textManager));
    story.append(new Activities::InputParameterActivity("Скорость на \"Зелёный\": %1 км/ч", context->speedGreen, textManager));
    story.append(new Activities::InputParameterActivity("Скорость на \"Жёлтый\": %1 км/ч", context->speedYellow, textManager));
    story.append(new Activities::InputParameterActivity("Длина пблок-участка: %1 м", context->sectionLength, textManager));
    story.append(new Activities::SubmitConfigurationActivity(context, textManager));
}

}
}
