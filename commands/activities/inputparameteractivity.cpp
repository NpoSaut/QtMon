#include "inputparameteractivity.h"

namespace Commands {
namespace Activities {

InputParameterActivity::InputParameterActivity(QString outputFormat, int* valueRef, TextManager *textManager, QObject *parent) :
    outputFormat (outputFormat), valueRef (valueRef),
    textManager (textManager), Activity(parent)
{
}

void InputParameterActivity::run()
{
    textManager->init(outputFormat, *valueRef);
    connect(textManager, SIGNAL(submitted(int)), SLOT(submitted()));
}

void InputParameterActivity::dispose()
{
    textManager->clear();
    disconnect(textManager, SIGNAL(submitted(int)), SLOT(submitted()));
}

void InputParameterActivity::submitted()
{
    *valueRef = textManager->getValue(); // Тут вообще я правильно написал???
    emit completed();
}

}
}
