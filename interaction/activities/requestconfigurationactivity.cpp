#include "requestconfigurationactivity.h"

namespace Interaction {
namespace Activities {

RequestConfigurationActivity::RequestConfigurationActivity(ConfigureContext *context, TextManager *textManager, QObject *parent)
    : context(context), textManager (textManager), Activity(parent)
{
}

void RequestConfigurationActivity::run()
{
    textManager->init("Запрос параметров...");
    // А здесь каким-то чудом надо запросить и заполнить контекст.
    // кукисы-пукисы и всё такое... я хз, чё с ними делать :(
    emit completed();
}

void RequestConfigurationActivity::dispose()
{
    textManager->clear();
}

}
}
