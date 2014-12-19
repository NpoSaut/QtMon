#ifndef AWAITMODULESACTIVITYACTIVITY_H
#define AWAITMODULESACTIVITYACTIVITY_H

#include <QObject>
#include "../activity.h"
#include "../textmanager.h"
#include "../contexts/modulesactivitycontext.h"
#include "qtBlokLib/parsers/mco_state.h"

namespace Interaction {
namespace Activities {

class AwaitModulesActivityActivity : public Activity
{
    Q_OBJECT
public:
    explicit AwaitModulesActivityActivity(Contexts::ModulesActivityContext *context, McoState *mcoState, TextManager *textManager, QObject *parent = 0);

    virtual void run ();
    virtual void dispose ();

private slots:
    void onMcoStateReceived ();

private:
    Contexts::ModulesActivityContext *context;
    McoState *mcoState;
    TextManager *textManager;

};

}
}

#endif // AWAITMODULESACTIVITYACTIVITY_H
