#include "RequestTrackNumberActivity.h"


Interaction::Activities::RequestTrackNumberActivity::RequestTrackNumberActivity(Interaction::Contexts::InputTrackNumberContext *context, Interaction::TextManager *textManager, QObject *parent) :
    context(context),
    RequestCookiesActivity(context, textManager, parent)
{ }

void Interaction::Activities::RequestTrackNumberActivity::dispose()
{
    RequestCookiesActivity::dispose();
    context->trackNumber = context->cookieRecord->value <= 15
            ? context->cookieRecord->value
            : context->cookieRecord->value - 15;
    context->regularity = context->cookieRecord->value <= 15 ? 0 : 1;
}
