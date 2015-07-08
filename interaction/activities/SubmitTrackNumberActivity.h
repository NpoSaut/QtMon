#ifndef SUBMITTRACKNUMBERACTIVITY_H
#define SUBMITTRACKNUMBERACTIVITY_H

#include "submitcookiesactivity.h"
#include "../contexts/InputTrackNumberContext.h"

namespace Interaction {
namespace Activities {

class SubmitTrackNumberActivity : public SubmitCookiesActivity
{
    Q_OBJECT
public:
    explicit SubmitTrackNumberActivity(Contexts::InputTrackNumberContext *context, TextManager *textManager, QObject *parent = 0);

    virtual void run ();

private:
    Contexts::InputTrackNumberContext *context;

};

}
}

#endif // SUBMITTRACKNUMBERACTIVITY_H
