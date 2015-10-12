#include "QSoundMouthFactory.h"
#include "QSoundMouth.h"

#include <QSound>

using namespace Sound;

QSoundMouthFactory::QSoundMouthFactory(QFileInfo warmUp)
{
    QSound::play(warmUp.absoluteFilePath()); // Неосознанный хак для QSound
}

IMouth *QSoundMouthFactory::produce(QObject *parent)
{
    return new QSoundMouth (parent);
}
