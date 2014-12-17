#include "executecommandactivity.h"

namespace Commands {
namespace Activities {

ExecuteCommandActivity::ExecuteCommandActivity(Commands::Contexts::ExecuteCommandContext *context, QObject *parent)
    : context (context)
{

}

void ExecuteCommandActivity::run()
{
    // Сюда вставить код, который запустит команду из CommandManager-а
    emit completed();
}

void ExecuteCommandActivity::dispose()
{

}

}
}
