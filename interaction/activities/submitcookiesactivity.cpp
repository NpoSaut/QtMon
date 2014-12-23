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

void SubmitCookiesActivity::processRecord(Contexts::CookiesContext::Record *p)
{
    if (p->cookie->isValid())
        if (p->cookie->getValue() == p->value)
            textManager->init(textManager->getOuputString().append("."));

    // Добавить обработку ошибки
    textManager->init(textManager->getOuputString().append("#"));
}

void SubmitCookiesActivity::run()
{
    textManager->init("Запись характеристик");
    CookiesActiviyBase::run();
}

void SubmitCookiesActivity::dispose()
{
    textManager->clear();
    CookiesActiviyBase::dispose();
}

}
}
