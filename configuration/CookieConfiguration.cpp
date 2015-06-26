#include "CookieConfiguration.h"

CookieConfiguration::CookieConfiguration(Cookie *cookie, QObject *parent)
    : BaseConfiguration (parent),
      cookie (cookie),
      forceSignal (false)
{
    QObject::connect(cookie, SIGNAL(updated(int,bool)), this, SLOT(onCookieUpdate(int,bool)));
}

void CookieConfiguration::update()
{
    forceSignal = true;
    cookie->requestValue(true);
}

void CookieConfiguration::onCookieUpdate(int value, bool valid)
{
    if (valid)
    {
        setBreakAssistRequired ((bool) (value & (1 << 0)), forceSignal);
        forceSignal = false;
    }
}
