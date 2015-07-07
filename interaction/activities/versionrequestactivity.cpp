#include <QStringList>

#include "versionrequestactivity.h"
#include "qtBlokLib/parsers/sys_diagnostics.h"

namespace Interaction {
namespace Activities {

VersionRequestActivity::VersionRequestActivity(QString moduleName, SysDiagnostics::AuxModule moduleId, QVector<AuxResourceVersion *> auxResources,
                                               Contexts::VersionRequestContext *context, ICan *can, TextManager *textManager,
                                               QObject *parent)
    : context (context), can (can), textManager (textManager), timer(),
      moduleName (moduleName), moduleId (moduleId), auxResources (auxResources), versionHandlers (auxResources.count()),
      Activity (parent)
{
    timer.setInterval(1000);
    timer.setSingleShot(true);
}

void VersionRequestActivity::run()
{
    for (int i = 0; i < auxResources.count(); i++)
    {
        versionHandlers[i] = new VersionRequestInternals::VersionHandler (auxResources[i], this);
        connect(versionHandlers[i], SIGNAL(updated()), this, SLOT(onVersionUpdate()));
    }
    connect (&timer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    // Запрос
    SysDiagnostics sd;
    sd.setModule(moduleId);
    sd.setOperation(SysDiagnostics::GET_VERSION);
    can->send(sd.encode());

    textManager->init(QString("Запрос версиии от модуля ") + moduleName + QString("..."));
    timer.start();
}

void VersionRequestActivity::dispose()
{
    textManager->clear();

    for (int i = 0; i < auxResources.count(); i++)
    {
        disconnect(versionHandlers[i], SIGNAL(updated()), this, SLOT(onVersionUpdate()));
        delete versionHandlers[i];
    }
    disconnect (&timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
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
        versionsString << QString("    ПК%1 ").arg(i+1) << versionHandlers[i]->toString();
//    versionsString.removeDuplicates();

    context->versionString = QString("Версия модуля ") + moduleName + ": " + versionsString.join(" ");
    emit completed();
}

VersionRequestInternals::VersionHandler::VersionHandler(AuxResourceVersion *auxResource, QObject *parent)
    : auxResource (auxResource), initialized(false), version (-1), subversion (-1), checksum (-1), QObject (parent)
{
    connect(auxResource, SIGNAL(messageReceived()), this, SLOT(update()));
}

VersionRequestInternals::VersionHandler::~VersionHandler()
{
    disconnect(auxResource, SIGNAL(messageReceived()), this, SLOT(update()));
}

QString VersionRequestInternals::VersionHandler::toString() const
{
    return initialized
            ? QString("%1.%2-%3").arg(version).arg(subversion).arg(quint8(checksum), 2, 16, QChar('0'))
            : QString("-----");
}

bool VersionRequestInternals::VersionHandler::operator ==(const VersionRequestInternals::VersionHandler &b) const
{
    return initialized == b.initialized && version == b.version && subversion == b.subversion && checksum == b.checksum;
}

bool VersionRequestInternals::VersionHandler::operator !=(const VersionRequestInternals::VersionHandler &b) const
{
    return !(*this == b);
}

void VersionRequestInternals::VersionHandler::update()
{
    initialized = true;
    version = auxResource->getVersion();
    subversion = auxResource->getSubversion();
    checksum = auxResource->getChecksum();
    emit updated ();
}

}
}
