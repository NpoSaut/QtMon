#include "modulesactivityactivity.h"

namespace Interaction {
namespace Activities {

ModulesActivityActivity::ModulesActivityActivity(TextManager *textManager, QObject *parent) :
    textManager(textManager), Activity(parent)
{
}

void ModulesActivityActivity::run()
{
    textManager->init("Конфигурация: 1234-6---AB-");
    connect(textManager, SIGNAL(submitted(int)), this, SLOT(submitted()));
}

void ModulesActivityActivity::dispose()
{
    textManager->clear();
    disconnect(textManager, SIGNAL(submitted(int)), this, SLOT(submitted()));
}

void ModulesActivityActivity::submitted()
{
    textManager->clear();
    emit completed();
}

}
}
