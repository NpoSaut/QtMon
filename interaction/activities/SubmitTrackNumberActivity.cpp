#include "SubmitTrackNumberActivity.h"

Interaction::Activities::SubmitTrackNumberActivity::SubmitTrackNumberActivity(Contexts::InputTrackNumberContext *context, TextManager *textManager, QObject *parent) :
    context(context),
    SubmitCookiesActivity(context, textManager, parent)
{ }

void Interaction::Activities::SubmitTrackNumberActivity::run()
{
    if (context->trackNumber < 0 || context->trackNumber > 15)
        context->trackNumber = 0;

    int val = context->trackNumber;
    if (context->trackNumber != 0 && context->regularity == 1)
        val += 15;
    context->cookieRecord->value = val;
    SubmitCookiesActivity::run();
}
