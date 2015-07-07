#ifndef COOKIESACTIVIYBASE_H
#define COOKIESACTIVIYBASE_H

#include <QVector>
#include "../activity.h"
#include "../contexts/cookiescontext.h"

namespace Interaction {
namespace Activities {

class CookiesActiviyBase : public Activity
{
    Q_OBJECT
public:
    explicit CookiesActiviyBase(Contexts::CookiesContext *context, QObject *parent = 0);

    virtual void run ();
    virtual void dispose ();

protected:
    virtual void startRecord (Contexts::CookiesContext::Record *p) = 0;
    virtual void processRecord (Contexts::CookiesContext::Record *p, int value, bool valid) = 0;

private slots:
    void cookieOnCompleted (int value, bool valid);

private:
    void next ();
    void attachCookie ();
    void detachCookie ();

    Contexts::CookiesContext *context;
    int i;
};

}
}

#endif // COOKIESACTIVIYBASE_H
