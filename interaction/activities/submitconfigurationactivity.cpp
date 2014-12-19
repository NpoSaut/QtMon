#include "submitconfigurationactivity.h"

namespace Interaction {
namespace Activities {

SubmitConfigurationActivity::SubmitConfigurationActivity(Contexts::ConfigureContext *context, TextManager *textManager, QObject *parent)
    : context (context), textManager (textManager), Activity(parent)
{

}

void SubmitConfigurationActivity::run()
{
    textManager->init("Запись характеристик...");
    // Ну, а сюда, соответсвенно, нужно сделать запись характеристик...
    emit completed();
}

void SubmitConfigurationActivity::dispose()
{
    textManager->clear();
}

}
}
