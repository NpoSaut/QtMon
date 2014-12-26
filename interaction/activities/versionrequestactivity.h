#ifndef VERSIONREQUESTACTIVITY_H
#define VERSIONREQUESTACTIVITY_H

#include <QObject>
#include <QTimer>
#include <QVector>
#include "../activity.h"
#include "../textmanager.h"
#include "../contexts/versionrequestcontext.h"
#include "qtCanLib/can.h"
#include "qtBlokLib/parsers/sys_diagnostics.h"
#include "qtBlokLib/parsers/aux_resource.h"

namespace Interaction {
namespace Activities {

namespace VersionRequestInternals {
class VersionHandler : public QObject
{
    Q_OBJECT
public:
    explicit VersionHandler (QObject *parent = 0);
    explicit VersionHandler (int version, int subversion, int checksum, QObject *parent = 0);

    bool isInitialized () const { return initialized; }
    int getVersion () const { return version; }
    int getSubversion () const { return subversion; }
    int getChecksum () const { return checksum; }

    QString toString () const;

    bool operator == (const VersionHandler &b) const;
    bool operator != (const VersionHandler &b) const;

public slots:
    void update (int version, int subversion, int checksum);

signals:
    void updated ();

private:
    bool initialized;
    int version;
    int subversion;
    int checksum;
};
}

class VersionRequestActivity : public Activity
{
    Q_OBJECT
public:
    explicit VersionRequestActivity(QString moduleName, SysDiagnostics::AuxModule moduleId, QVector<AuxResourceVersion *> auxResources,
                                    Contexts::VersionRequestContext *context, Can *can, TextManager *textManager,
                                    QObject *parent = 0);

    virtual void run ();
    virtual void dispose ();

    ~VersionRequestActivity ();

private slots:
    void onVersionUpdate ();
    void onTimeout ();

private:
    void baybay ();

    Contexts::VersionRequestContext *context;
    Can *can;
    TextManager *textManager;
    QTimer timer;

    QString moduleName;
    SysDiagnostics::AuxModule moduleId;
    QVector<AuxResourceVersion *> auxResources;
    QVector<VersionRequestInternals::VersionHandler *> versionHandlers;
};

}
}

#endif // VERSIONREQUESTACTIVITY_H
