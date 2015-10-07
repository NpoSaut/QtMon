#ifndef QSOUNDMOUTH_H
#define QSOUNDMOUTH_H

#include "IMouth.h"

namespace Sound {

class QSoundMouth : public IMouth
{
public:
    QSoundMouth();

    virtual void say (QFileInfo file);
};

}


#endif // QSOUNDMOUTH_H
