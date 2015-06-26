#include "submitcookiesactivity.h"

namespace Interaction {
namespace Activities {

SubmitCookiesActivity::SubmitCookiesActivity(Contexts::CookiesContext *context, TextManager *textManager, QObject *parent)
    : context (context), textManager (textManager), CookiesActiviyBase (context, parent)
{
}

void SubmitCookiesActivity::startRecord(Contexts::CookiesContext::Record *p)
{
    p->cookie->setVaule(p->value);
}

void SubmitCookiesActivity::processRecord(Contexts::CookiesContext::Record *p, int value, bool valid)
{
    if (valid && value == p->value)
    {
        textManager->init(textManager->getOuputString().append("."));
    }
    else
    {
        textManager->init(textManager->getOuputString().append("◊"));
        context->resultMessage = context->failureMessageText;
    }
}

void SubmitCookiesActivity::run()
{
    textManager->init("Запись характеристик");
    context->resultMessage = context->successMessageText;
    CookiesActiviyBase::run();
}

void SubmitCookiesActivity::dispose()
{
    textManager->clear();
    CookiesActiviyBase::dispose();
}

}
}
