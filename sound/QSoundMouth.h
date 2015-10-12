#ifndef QSOUNDMOUTH_H
#define QSOUNDMOUTH_H

#include "IMouth.h"

namespace Sound {

class QSoundMouth : public IMouth
{
public:
    QSoundMouth(QObject *parent = 0);

    virtual void say (QFileInfo file);

private:
    QObject *parent;
};

}


#endif // QSOUNDMOUTH_H
