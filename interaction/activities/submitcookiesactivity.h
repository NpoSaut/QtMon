#ifndef SUBMITCOOKIESACTIVITY_H
#define SUBMITCOOKIESACTIVITY_H


#include "cookiesactiviybase.h"
#include "../textmanager.h"

namespace Interaction {
namespace Activities {

class SubmitCookiesActivity : public CookiesActiviyBase
{
    Q_OBJECT
public:
    explicit SubmitCookiesActivity(Contexts::CookiesContext *context, TextManager *textManager, QObject *parent = 0);

    virtual void startRecord (Contexts::CookiesContext::Record *p);
    virtual void processRecord (Contexts::CookiesContext::Record *p);

    void run();
    void dispose();

private:
    Contexts::CookiesContext *context;
    TextManager *textManager;
};

}
}

#endif // SUBMITCOOKIESACTIVITY_H
