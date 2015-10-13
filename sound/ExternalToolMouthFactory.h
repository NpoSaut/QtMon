#ifndef EXTERNALTOOLMOUTHFACTORY_H
#define EXTERNALTOOLMOUTHFACTORY_H

#include <QString>

#include "IMouthFactory.h"

namespace Sound {

class ExternalToolMouthFactory : public IMouthFactory
{
public:
    ExternalToolMouthFactory(QString command); // %1 будет заменено на воспроизводимый файл

    virtual IMouth *produce (QObject *parent = 0);

private:
    QString command;
};

}

#endif // EXTERNALTOOLMOUTHFACTORY_H
