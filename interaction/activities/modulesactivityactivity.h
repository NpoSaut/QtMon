#ifndef MODULESACTIVITYACTIVITY_H
#define MODULESACTIVITYACTIVITY_H

#include <QObject>
#include "../activity.h"
#include "../textmanager.h"

namespace Interaction {
namespace Activities {

class ModulesActivityActivity : public Activity
{
    Q_OBJECT
public:
    explicit ModulesActivityActivity(TextManager *textManager, QObject *parent = 0);

    virtual void run ();
    virtual void dispose ();

public slots:
    void submitted ();

private:
    TextManager *textManager;
};

}
}

#endif // MODULESACTIVITYACTIVITY_H
