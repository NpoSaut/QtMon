#include "InputTrackNumberCommand.h"
#include "../contexts/InputTrackNumberContext.h"
#include "../activities/RequestTrackNumberActivity.h"
#include "../activities/inputactivity.h"
#include "../activities/SubmitTrackNumberActivity.h"

Interaction::Commands::InputTrackNumberCommand::InputTrackNumberCommand(Cookies *cookies, Interaction::TextManager *textManager)
    : cookies (cookies), textManager (textManager), Command (-1)
{ }

Interaction::Story *Interaction::Commands::InputTrackNumberCommand::createStory()
{
    auto *context = new Contexts::InputTrackNumberContext(cookies);
    return new Story(context, {
                            new Activities::RequestTrackNumberActivity(context, textManager),
                            new Activities::InputActivity("Номер пути: %1", &context->trackNumber, textManager),
                            new Activities::InputActivity("Признак правильности пути: %1 (0 - Н, 1 - П)", &context->regularity, textManager),
                            new Activities::SubmitTrackNumberActivity(context, textManager)
                        });
}
