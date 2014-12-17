#include "inputcommandactivity.h"

namespace Commands {
namespace Activities {

InputCommandActivity::InputCommandActivity(TextManager *textManager, QObject *parent) :
    textManager (textManager), Activity(parent)
{
}

void InputCommandActivity::run()
{
    textManager->setOutputFormat("Комманда: %1");
    connect(textManager, SIGNAL(submitted(int)), SLOT(submitted()));
}

void InputCommandActivity::dispose()
{

}

void InputCommandActivity::submitted()
{

}

}
}
