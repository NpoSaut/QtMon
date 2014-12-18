#ifndef REQUESTCONFIGURATIONACTIVITY_H
#define REQUESTCONFIGURATIONACTIVITY_H

#include "../activity.h"
#include "../contexts/configurecontext.h"
#include "../textmanager.h"

namespace Interaction {
namespace Activities {

class RequestConfigurationActivity : public Activity
{
    Q_OBJECT
public:
    explicit RequestConfigurationActivity(Contexts::ConfigureContext *context, TextManager *textManager, QObject *parent = 0);

    virtual void run ();
    virtual void dispose ();

signals:
    void completed ();
    void canselled ();

private:
    Contexts::ConfigureContext *context;
    TextManager *textManager;

};

}
}

#endif // REQUESTCONFIGURATIONACTIVITY_H
