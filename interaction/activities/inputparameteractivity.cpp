#include "inputparameteractivity.h"

namespace Interaction {
namespace Activities {

InputParameterActivity::InputParameterActivity(QString outputFormat, int *value, TextManager *textManager, QObject *parent) :
    outputFormat (outputFormat), value (value),
    textManager (textManager), Activity(parent)
{
}

void InputParameterActivity::run()
{
    textManager->init(outputFormat, *value);
    connect(textManager, SIGNAL(submitted(int)), this, SLOT(submitted()));
}

void InputParameterActivity::dispose()
{
    textManager->clear();
    disconnect(textManager, SIGNAL(submitted(int)), this, SLOT(submitted()));
}

void InputParameterActivity::submitted()
{
    *value = textManager->getValue();
    emit completed();
}

}
}
