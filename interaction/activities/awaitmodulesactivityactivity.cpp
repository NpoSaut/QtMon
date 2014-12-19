#include "awaitmodulesactivityactivity.h"

namespace Interaction {
namespace Activities {

AwaitModulesActivityActivity::AwaitModulesActivityActivity(Contexts::ModulesActivityContext *context, McoState *mcoState, TextManager *textManager, QObject *parent) :
    context (context), mcoState (mcoState), textManager(textManager), Activity(parent)
{
}

void AwaitModulesActivityActivity::run()
{
    textManager->init("Ожидаем сообщения от ЦО...");
    connect(mcoState, SIGNAL(messageReceived()), this, SLOT(onMcoStateReceived()));
}

void AwaitModulesActivityActivity::dispose()
{
    textManager->clear();
    disconnect(mcoState, SIGNAL(messageReceived()), this, SLOT(onMcoStateReceived()));
}

void AwaitModulesActivityActivity::onMcoStateReceived()
{
    context->activityString = mcoState->getModulesActivity().toString();
    emit completed();
}

}
}
