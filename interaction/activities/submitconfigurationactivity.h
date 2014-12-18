#ifndef SUBMITCONFIGURATIONACTIVITY_H
#define SUBMITCONFIGURATIONACTIVITY_H


#include "../activity.h"
#include "../textmanager.h"
#include "../contexts/configurecontext.h"

namespace Interaction {
namespace Activities {

class SubmitConfigurationActivity : public Activity
{
    Q_OBJECT
public:
    explicit SubmitConfigurationActivity(Contexts::ConfigureContext *context, TextManager *textManager, QObject *parent = 0);

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

#endif // SUBMITCONFIGURATIONACTIVITY_H
