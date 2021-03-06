#include "requestcookiesactivity.h"

namespace Interaction {
namespace Activities {

RequestCookiesActivity::RequestCookiesActivity(Contexts::CookiesContext *context, TextManager *textManager, QObject *parent)
    : context (context), textManager (textManager), CookiesActiviyBase (context, parent)
{
}

void RequestCookiesActivity::startRecord(Contexts::CookiesContext::Record *p)
{
    p->cookie->requestValue(true);
}

void RequestCookiesActivity::processRecord(Contexts::CookiesContext::Record *p, int value, bool valid)
{
    if (valid)
        p->value = value;
    else
        p->value = -1;

    textManager->init(textManager->getOuputString().append("."));
}

void RequestCookiesActivity::run()
{
    textManager->init("Запрос параметров");
    CookiesActiviyBase::run();
}

void RequestCookiesActivity::dispose()
{
    textManager->clear();
    CookiesActiviyBase::dispose();
}

}
}
