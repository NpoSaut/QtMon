#include "ExternalToolMouthFactory.h"

#include "ExternalToolMouth.h"

using namespace Sound;

ExternalToolMouthFactory::ExternalToolMouthFactory(QString command) :
    command (command)
{ }

IMouth *ExternalToolMouthFactory::produce(QObject *parent)
{
    return new ExternalToolMouth (command, parent);
}
