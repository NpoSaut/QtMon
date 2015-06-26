#ifndef COOKIECONFIGURATION_H
#define COOKIECONFIGURATION_H

#include "BaseConfiguration.h"
#include "qtBlokLib/cookies.h"

class CookieConfiguration : public BaseConfiguration
{
    Q_OBJECT
public:
    CookieConfiguration(Cookie *cookie, QObject *parent = 0);

public slots:
    virtual void update ();

private slots:
    void onCookieUpdate (int value, bool valid);

private:
    Cookie *cookie;
    bool forceSignal;
};

#endif // COOKIECONFIGURATION_H
