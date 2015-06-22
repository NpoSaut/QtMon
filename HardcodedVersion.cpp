#include "HardcodedVersion.h"

HardcodedVersion::HardcodedVersion(int version, int subversion, Can *can, QObject *parent) :
    QObject(parent), can (can), aux (AuxResource::Descriptor::BIL_A, this)
{
    aux.setVersion(version);
    aux.setSubversion(subversion);

    can->transmitMessage(aux.encode());
}

void HardcodedVersion::onVersionRequest(SysDiagnostics::AuxModule blockId)
{
    if (blockId == SysDiagnostics::AuxModule::BIL)
        can->transmitMessage(aux.encode());
}
