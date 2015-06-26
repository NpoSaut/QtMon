#include "cookiesactiviybase.h"

namespace Interaction {
namespace Activities {

CookiesActiviyBase::CookiesActiviyBase(Contexts::CookiesContext *context, QObject *parent)
    : context (context), i (-1), Activity (parent)
{

}

void CookiesActiviyBase::run()
{
    next ();
}

void CookiesActiviyBase::dispose()
{
    detachCookie();
}

void CookiesActiviyBase::cookieOnCompleted(int value, bool valid)
{
    processRecord (&context->records[i], value, valid);
    next ();
}

void CookiesActiviyBase::next()
{
    detachCookie();
    i ++;
    attachCookie();

    if (i < context->records.count())
        startRecord (&context->records[i]);
    else
        emit completed();
}

void CookiesActiviyBase::attachCookie()
{
    if ( i >= 0 && i < context->records.count() )
        connect (context->records[i].cookie, SIGNAL(updated(int,bool)), this, SLOT(cookieOnCompleted(int,bool)));
}

void CookiesActiviyBase::detachCookie()
{
    if ( i >= 0 && i < context->records.count() )
        disconnect (context->records[i].cookie, SIGNAL(updated(int,bool)), this, SLOT(cookieOnCompleted(int,bool)));
}

}
}

//pairs ({
//             {&pairs->categoryTrain, &context->trainCategory},
//             {&pairs->timeshift,&context->summerTime},
//             {&pairs->locomotiveKind, context->locomotiveKind},
//             {&pairs->locomotiveNumber, context->locomotiveNumber},
//             {&pairs->diameter1, context->diameter1},
//             {&pairs->diameter2, context->diameter2},
//             {&pairs->dpsDentos, context->impulsesPerCycle},
//             {&pairs->configuration, context->configuration},
//             {&pairs->speedLimitWhite, context->speedWhite},
//             {&pairs->speedLimitGreen, context->speedGreen},
//             {&pairs->speedLimitRedYellow, context->speedYellow},
//             {&pairs->dozorLength, context->sectionLength},
//            })
