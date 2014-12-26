#include <QStringList>

#include "versionrequestactivity.h"
#include "qtBlokLib/parsers/sys_diagnostics.h"

namespace Interaction {
namespace Activities {

VersionRequestActivity::VersionRequestActivity(QString moduleName, SysDiagnostics::AuxModule moduleId, QVector<AuxResourceVersion *> auxResources,
                                               Contexts::VersionRequestContext *context, Can *can, TextManager *textManager,
                                               QObject *parent)
    : context (context), can (can), textManager (textManager), timer(),
      moduleName (moduleName), moduleId (moduleId), auxResources (auxResources), versionHandlers (auxResources.count()),
      Activity (parent)
{
    for(int i = 0; i < versionHandlers.count(); i ++)
        versionHandlers[i] = new VersionRequestInternals::VersionHandler ();

    timer.setInterval(1000);
    timer.setSingleShot(true);
}

void VersionRequestActivity::run()
{
    for (int i = 0; i < auxResources.count(); i++)
    {
        QObject::connect(auxResources[i], SIGNAL(updated(int,int,int)), versionHandlers[i], SLOT(update(int,int,int)));
        connect(versionHandlers[i], SIGNAL(updated()), this, SLOT(onVersionUpdate()));
    }
    connect (&timer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    // Запрос
    SysDiagnostics sd;
    sd.setModule(moduleId);
    sd.setOperation(SysDiagnostics::GET_VERSION);
    can->transmitMessage(sd.encode());

    textManager->init(QString("Запрос версиии от модуля ") + moduleName + QString("..."));
    timer.start();
}

void VersionRequestActivity::dispose()
{
    textManager->clear();

    for (int i = 0; i < auxResources.count(); i++)
    {
        disconnect(auxResources[i], SIGNAL(updated(int,int,int)), versionHandlers[i], SLOT(update(int,int,int)));
        disconnect(versionHandlers[i], SIGNAL(updated()), this, SLOT(onVersionUpdate()));
    }
    disconnect (&timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

VersionRequestActivity::~VersionRequestActivity()
{
    for(int i = 0; i < versionHandlers.count(); i ++)
        delete versionHandlers[i];
}

void VersionRequestActivity::onVersionUpdate()
{
    bool allReady = true;
    for (int i = 0; i < versionHandlers.count(); i++)
        allReady = allReady && versionHandlers[i]->isInitialized();

    if (allReady)
        baybay();
}

void VersionRequestActivity::onTimeout()
{
    baybay();
}

void VersionRequestActivity::baybay()
{
    QStringList versionsString;
    for (int i = 0; i < versionHandlers.count(); i++)
        versionsString << versionHandlers[i]->toString();
    versionsString.removeDuplicates();

    context->versionString = QString("Версия модуля ") + moduleName + ": " + versionsString.join(" | ") + ".";
    emit completed();
}

VersionRequestInternals::VersionHandler::VersionHandler(QObject *parent)
    : initialized (false), version (-1), subversion(-1), QObject (parent)
{ }

VersionRequestInternals::VersionHandler::VersionHandler(int version, int subversion, int checksum, QObject *parent)
    : initialized(true), version (version), subversion (subversion), checksum (checksum), QObject (parent)
{ }

QString VersionRequestInternals::VersionHandler::toString() const
{
    return initialized
            ? QString("%1.%2/%3").arg(version).arg(subversion).arg(checksum, 4, 16)
            : QString("-");
}

bool VersionRequestInternals::VersionHandler::operator ==(const VersionRequestInternals::VersionHandler &b) const
{
    return initialized == b.initialized && version == b.version && subversion == b.subversion && checksum == b.checksum;
}

bool VersionRequestInternals::VersionHandler::operator !=(const VersionRequestInternals::VersionHandler &b) const
{
    return !(*this == b);
}

void VersionRequestInternals::VersionHandler::update(int version, int subversion, int checksum)
{
    initialized = true;
    this->version = version;
    this->subversion = subversion;
    this->checksum = checksum;
}

}
}
