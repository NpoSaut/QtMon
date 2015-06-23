#include "executecommandactivity.h"

namespace Interaction {
namespace Activities {

ExecuteCommandActivity::ExecuteCommandActivity(Contexts::ExecuteCommandContext *context, CommandManager *commandManager, QObject *parent)
    : context (context), commandManager (commandManager), Activity (parent)
{

}

void ExecuteCommandActivity::run()
{
    commandManager->executeCommand(context->commandNumber);
    emit completed();
}

void ExecuteCommandActivity::dispose()
{

}

}
}
