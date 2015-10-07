#ifndef IMOUTH_H
#define IMOUTH_H

#include <QFileInfo>

namespace Sound {

class IMouth
{
public:
    virtual void say (QFileInfo file) = 0;
};

}

#endif // IMOUTH_H
