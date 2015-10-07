#include "QSoundMouth.h"

#include <QSound>

using namespace Sound;

QSoundMouth::QSoundMouth()
{ }

void QSoundMouth::say(QFileInfo file)
{
    QSound mouth(file.absoluteFilePath());
    mouth.play();
    while (!mouth.isFinished());
}
