#include "configurecommand.h"
#include "../contexts/configurecontext.h"
#include "../activities/inputparameteractivity.h"
#include "../activities/requestconfigurationactivity.h"
#include "../activities/submitconfigurationactivity.h"

namespace Interaction {
namespace Commands {

ConfigureCommand::ConfigureCommand(TextManager *textManager)
    : textManager (textManager), Command (5)
{
}

Story *ConfigureCommand::createStory()
{
    auto *context = new Contexts::ConfigureContext();
    Story *story = new Story(context, {
                                new Activities::RequestConfigurationActivity(context, textManager),
                                new Activities::InputParameterActivity("Категория поезда: %1", &context->trainCategory, textManager),
                                new Activities::InputParameterActivity("Время: %1 (0 - зимнее, 1 - летнее)", &context->summerTime, textManager),
                                new Activities::InputParameterActivity("Тип локомотива: %1", &context->locomotiveKind, textManager),
                                new Activities::InputParameterActivity("Номер локомотива: %1", &context->locomotiveNumber, textManager),
                                new Activities::InputParameterActivity("Диаметр бандажа колеса 1: %1 мм", &context->diameter1, textManager),
                                new Activities::InputParameterActivity("Диаметр бандажа колеса 2: %1 мм", &context->diameter2, textManager),
                                new Activities::InputParameterActivity("Число зубьев ДС: %1", &context->impulsesPerCycle, textManager),
                                new Activities::InputParameterActivity("Конфигурация: %1", &context->configuration, textManager),
                                new Activities::InputParameterActivity("Скорость на \"Белый\": %1 км/ч", &context->speedWhite, textManager),
                                new Activities::InputParameterActivity("Скорость на \"Зелёный\": %1 км/ч", &context->speedGreen, textManager),
                                new Activities::InputParameterActivity("Скорость на \"Жёлтый\": %1 км/ч", &context->speedYellow, textManager),
                                new Activities::InputParameterActivity("Длина пблок-участка: %1 м", &context->sectionLength, textManager),
                                new Activities::SubmitConfigurationActivity(context, textManager)
                             });
    return story;
}

}
}
