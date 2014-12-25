#ifndef DISPLAYMODULESACTIVITYACTIVITY_H
#define DISPLAYMODULESACTIVITYACTIVITY_H

#include <QObject>
#include <QTimer>
#include "../activity.h"
#include "../textmanager.h"
#include "qtBlokLib/parsers/mco_state.h"

namespace Interaction {
namespace Activities {

class DisplayModulesActivityActivity : public Activity
{
    Q_OBJECT
public:
    explicit DisplayModulesActivityActivity(McoState *mcoState, TextManager *textManager, QObject *parent = 0);

    virtual void run ();
    virtual void dispose ();

private slots:
    void onMcoStateReceived ();
    void onFoulTimeout ();

private:
    McoState *mcoState;
    TextManager *textManager;
    QTimer foulTimer;
};

}
}

#endif // DISPLAYMODULESACTIVITYACTIVITY_H
