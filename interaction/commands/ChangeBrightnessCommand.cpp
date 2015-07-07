#include "ChangeBrightnessCommand.h"
#include "../contexts/changebrightnesscontext.h"
#include "../activities/inputactivity.h"
#include "../activities/changebrightnessactivity.h"


Interaction::Commands::ChangeBrightnessCommand::ChangeBrightnessCommand(IIlluminationManager *illuminationManager, Interaction::TextManager *textManager) :
    illuminationManager(illuminationManager), textManager(textManager),
    Command(-1)
{ }

Interaction::Story *Interaction::Commands::ChangeBrightnessCommand::createStory()
{
    auto *context = new Contexts::ChangeBrightnessContext(illuminationManager->illumination() * 10);
    return new Story(context, {
                            new Activities::InputActivity("Установить яркость: %1 (0-10)", &context->brightness, textManager),
                            new Activities::ChangeBrightnessActivity(context, illuminationManager)
                        });
}
