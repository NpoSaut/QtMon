#include "CookieConfiguration.h"

CookieConfiguration::CookieConfiguration(Cookie *cookie)
    : breakAssistRequired (false)
{
    int config = cookie->getValue();
    if (cookie->isValid())
    {
        breakAssistRequired = (bool) (config & (1 << 0));
    }
}

bool CookieConfiguration::isBreakAssistRequired() const
{
    return breakAssistRequired;
}
