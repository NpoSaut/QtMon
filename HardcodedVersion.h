#ifndef HARDCODEDVERSION_H
#define HARDCODEDVERSION_H

#include <QObject>
#include <qtCanLib/ICan.h>
#include <qtBlokLib/parsers/aux_resource.h>
#include <qtBlokLib/parsers/sys_diagnostics.h>

class HardcodedVersion : public QObject
{
    Q_OBJECT
public:
    explicit HardcodedVersion(int version, int subversion, ICan *can, QObject *parent = 0);

signals:

public slots:
    void onVersionRequest (SysDiagnostics::AuxModule blockId);

private:
    ICan *can;
    AuxResourceVersion aux;
};

#endif // HARDCODEDVERSION_H
