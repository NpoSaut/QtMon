#ifndef EXTERNALTOOLMOUTHFACTORY_H
#define EXTERNALTOOLMOUTHFACTORY_H

#include <QString>

#include "IMouthFactory.h"

namespace Sound {

class ExternalToolMouthFactory : public IMouthFactory
{
public:
    ExternalToolMouthFactory(QString &command);

    virtual IMouth *produce (QObject *parent = 0);

private:
    QString command;
};

}

#endif // EXTERNALTOOLMOUTHFACTORY_H
