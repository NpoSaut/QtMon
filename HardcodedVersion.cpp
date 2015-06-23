#include "HardcodedVersion.h"
#include <QFile>
#include <QCoreApplication>
#include <QCryptographicHash>

HardcodedVersion::HardcodedVersion(int version, int subversion, Can *can, QObject *parent) :
    QObject(parent), can (can), aux (AuxResource::Descriptor::BIL_A, this)
{
    aux.setVersion(version);
    aux.setSubversion(subversion);

    QFile mainFile(QCoreApplication::applicationFilePath());
    if (mainFile.open(QIODevice::ReadOnly))
    {
        QByteArray cs = QCryptographicHash::hash(mainFile.readAll(), QCryptographicHash::Sha1);
        aux.setChecksum(int(cs[1])*256 + cs[0]);
    }

    can->transmitMessage(aux.encode());
}

void HardcodedVersion::onVersionRequest(SysDiagnostics::AuxModule blockId)
{
    if (blockId == SysDiagnostics::AuxModule::BIL)
        can->transmitMessage(aux.encode());
}
