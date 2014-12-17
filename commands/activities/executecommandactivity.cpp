#include "executecommandactivity.h"

namespace Commands {
namespace Activities {

ExecuteCommandActivity::ExecuteCommandActivity(Commands::Contexts::ExecuteCommandContext *context, QObject *parent)
    : context (context), commandManager (commandManager)
{

}

void ExecuteCommandActivity::run()
{
    commandManager->ExecuteCommand(context->commandNumber);
    emit completed();
}

void ExecuteCommandActivity::dispose()
{

}

}
}
