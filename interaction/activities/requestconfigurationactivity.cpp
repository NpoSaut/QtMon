#include "requestconfigurationactivity.h"

namespace Interaction {
namespace Activities {

RequestConfigurationActivity::RequestConfigurationActivity(Contexts::ConfigureContext *context, TextManager *textManager, QObject *parent)
    : context(context), textManager (textManager), Activity(parent)
{
}

void RequestConfigurationActivity::run()
{
    textManager->init("Запрос параметров...");

    context->trainCategory = 0;
    context->summerTime = 0;
    context->locomotiveKind = 0;
    context->locomotiveNumber = 0;
    context->diameter1 = 0;
    context->diameter2 = 0;
    context->impulsesPerCycle = 0;
    context->configuration = 0;
    context->speedWhite = 0;
    context->speedGreen = 0;
    context->speedYellow = 0;
    context->sectionLength = 0;

    emit completed();
}

void RequestConfigurationActivity::dispose()
{
    textManager->clear();
}

}
}
