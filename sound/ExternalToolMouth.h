#ifndef EXTERNALTOOLMOUTH_H
#define EXTERNALTOOLMOUTH_H

#include <QProcess>

#include "IMouth.h"

namespace Sound {

class ExternalToolMouth : public IMouth
{
public:
    explicit ExternalToolMouth(const QString &program, QObject *parent = 0);

    virtual void say (QFileInfo file);

private:
    QProcess process;
    QString program;
};

}

#endif // EXTERNALTOOLMOUTH_H
