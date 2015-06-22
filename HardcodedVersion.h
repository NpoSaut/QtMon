#ifndef HARDCODEDVERSION_H
#define HARDCODEDVERSION_H

#include <QObject>
#include <qtCanLib/can.h>
#include <qtBlokLib/parsers/aux_resource.h>
#include <qtBlokLib/parsers/sys_diagnostics.h>

class HardcodedVersion : public QObject
{
    Q_OBJECT
public:
    explicit HardcodedVersion(int version, int subversion, Can *can, QObject *parent = 0);

signals:

public slots:
    void onVersionRequest (SysDiagnostics::AuxModule blockId);

private:
    Can *can;
    AuxResourceVersion aux;
};

#endif // HARDCODEDVERSION_H
