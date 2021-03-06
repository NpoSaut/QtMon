#ifndef REQUESTCOOKIESACTIVITY_H
#define REQUESTCOOKIESACTIVITY_H

#include "cookiesactiviybase.h"
#include "../textmanager.h"

namespace Interaction {
namespace Activities {

class RequestCookiesActivity : public CookiesActiviyBase
{
    Q_OBJECT
public:
    explicit RequestCookiesActivity(Contexts::CookiesContext *context, TextManager *textManager, QObject *parent = 0);

    virtual void startRecord (Contexts::CookiesContext::Record *p);
    virtual void processRecord (Contexts::CookiesContext::Record *p, int value, bool valid);

    void run();
    void dispose();

private:
    Contexts::CookiesContext *context;
    TextManager *textManager;
};

}
}

#endif // REQUESTCOOKIESACTIVITY_H
