#include "QSoundMouth.h"

#include <QSound>

using namespace Sound;

QSoundMouth::QSoundMouth(QObject *parent)
    : parent (parent)
{ }

void QSoundMouth::say(QFileInfo file)
{
    QSound mouth(file.absoluteFilePath(), parent);
    mouth.play();
    while (!mouth.isFinished());
}
