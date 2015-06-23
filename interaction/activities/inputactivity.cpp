#include "inputactivity.h"

namespace Interaction {
namespace Activities {

InputActivity::InputActivity(QString outputFormat, int *value, TextManager *textManager, QObject *parent) :
    outputFormat (outputFormat), value (value),
    textManager (textManager), Activity(parent)
{
}

void InputActivity::run()
{
    textManager->init(outputFormat, value ? *value : 0);
    connect(textManager, SIGNAL(submitted(int)), this, SLOT(submitted()));
}

void InputActivity::dispose()
{
    textManager->clear();
    disconnect(textManager, SIGNAL(submitted(int)), this, SLOT(submitted()));
}

void InputActivity::submitted()
{
    if (value)
        *value = textManager->getValue();
    emit completed();
}

}
}
