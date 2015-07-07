#ifndef REQUESTTRACKNUMBERACTIVITY_H
#define REQUESTTRACKNUMBERACTIVITY_H

#include "requestcookiesactivity.h"
#include "../contexts/InputTrackNumberContext.h"

namespace Interaction {
namespace Activities {

class RequestTrackNumberActivity : public RequestCookiesActivity
{
    Q_OBJECT
public:
    RequestTrackNumberActivity(Contexts::InputTrackNumberContext *context, TextManager *textManager, QObject *parent = 0);

    virtual void dispose ();

private:
    Contexts::InputTrackNumberContext *context;

};

}
}

#endif // REQUESTTRACKNUMBERACTIVITY_H
