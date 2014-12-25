#include "displaymodulesactivityactivity.h"

namespace Interaction {
namespace Activities {

DisplayModulesActivityActivity::DisplayModulesActivityActivity(McoState *mcoState, TextManager *textManager, QObject *parent) :
    mcoState (mcoState), textManager(textManager), foulTimer(), Activity(parent)
{
    foulTimer.setInterval(1000);
    foulTimer.setSingleShot(true);
    connect (&foulTimer, SIGNAL(timeout()), this, SLOT(onFoulTimeout()));
}

void DisplayModulesActivityActivity::run()
{
    textManager->init("Ожидаем сообщения от ЦО...");
    connect(mcoState, SIGNAL(messageReceived()), this, SLOT(onMcoStateReceived()));
}

void DisplayModulesActivityActivity::dispose()
{
    textManager->clear();
    disconnect(mcoState, SIGNAL(messageReceived()), this, SLOT(onMcoStateReceived()));
}

void DisplayModulesActivityActivity::onMcoStateReceived()
{
    textManager->init(QString("Конфигурация: ") + mcoState->getModulesActivity().toString());
    foulTimer.start();
}

void DisplayModulesActivityActivity::onFoulTimeout()
{
    textManager->init(textManager->getOuputString() + " (нет сообщений от ЦО)");
}

}
}
