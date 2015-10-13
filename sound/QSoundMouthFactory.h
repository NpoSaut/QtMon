#ifndef QSOUNDMOUTHFACTORY_H
#define QSOUNDMOUTHFACTORY_H

#include "IMouthFactory.h"

namespace Sound {

class QSoundMouthFactory : public IMouthFactory
{
public:
    // Файл warmUp будет воспроизведён при создании фабрики,
    // его нужно воспроизвести из потока QApplication, чтобы заработал QSound.
    QSoundMouthFactory(QFileInfo warmUp);

    virtual IMouth *produce (QObject *parent = 0);
};

}

#endif // QSOUNDMOUTHFACTORY_H
