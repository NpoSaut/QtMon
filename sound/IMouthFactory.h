#ifndef IMOUTHFACTORY_H
#define IMOUTHFACTORY_H

#include "IMouth.h"

namespace Sound {

class IMouthFactory
{
public:
    virtual IMouth *produce (QObject *parent = 0) =0;
};

}

#endif // IMOUTHFACTORY_H
