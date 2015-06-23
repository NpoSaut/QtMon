#ifndef COOKIECONFIGURATION_H
#define COOKIECONFIGURATION_H

#include "IConfiguration.h"
#include "qtBlokLib/cookies.h"

class CookieConfiguration : public IConfiguration
{
public:
    CookieConfiguration(Cookie *cookie);

    virtual bool isBreakAssistRequired() const;

private:
    bool breakAssistRequired;
};

#endif // COOKIECONFIGURATION_H
