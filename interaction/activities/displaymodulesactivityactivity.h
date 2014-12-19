#ifndef DISPLAYMODULESACTIVITYACTIVITY_H
#define DISPLAYMODULESACTIVITYACTIVITY_H

#include <QObject>
#include "../activity.h"
#include "../textmanager.h"
#include "../contexts/modulesactivitycontext.h"

namespace Interaction {
namespace Activities {

class DisplayModulesActivityActivity : public Activity
{
    Q_OBJECT
public:
    explicit DisplayModulesActivityActivity(Contexts::ModulesActivityContext *context, TextManager *textManager, QObject *parent = 0);

    virtual void run ();
    virtual void dispose ();

private:
    Contexts::ModulesActivityContext *context;
    TextManager *textManager;
};

}
}

#endif // DISPLAYMODULESACTIVITYACTIVITY_H
