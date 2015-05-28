#include "changebrightnessactivity.h"

Interaction::Activities::ChangeBrightnessActivity::ChangeBrightnessActivity(Interaction::Contexts::ChangeBrightnessContext *context, IIlluminationManager *illuminationsManager, QObject *parent) :
    _context(context), _illuminationsManager(illuminationsManager), Activity(parent)
{

}

void Interaction::Activities::ChangeBrightnessActivity::run()
{
    if (_context->brightness <  0) _context->brightness =  0;
    if (_context->brightness > 10) _context->brightness = 10;
    _illuminationsManager->setIllumination(_context->brightness * 0.1);
}
