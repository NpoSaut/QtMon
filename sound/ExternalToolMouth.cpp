#include "ExternalToolMouth.h"

using namespace Sound;

ExternalToolMouth::ExternalToolMouth(const QString &program, QObject *parent) :
    process (parent),
    program (program)
{
}

void ExternalToolMouth::say(QFileInfo file)
{
    process.start(program + file.absoluteFilePath());
    process.waitForFinished();
}
