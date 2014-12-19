#include "displaymodulesactivityactivity.h"

namespace Interaction {
namespace Activities {

DisplayModulesActivityActivity::DisplayModulesActivityActivity(Contexts::ModulesActivityContext *context, TextManager *textManager, QObject *parent) :
    context(context), textManager(textManager), Activity(parent)
{
}

void DisplayModulesActivityActivity::run()
{
    textManager->init(QString("Конфигурация: ") + context->activityString);
}

void DisplayModulesActivityActivity::dispose()
{
    textManager->clear();
}

}
}
