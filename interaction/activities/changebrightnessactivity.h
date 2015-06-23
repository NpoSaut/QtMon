#ifndef CHANGEBRIGHTNESSACTIVITY_H
#define CHANGEBRIGHTNESSACTIVITY_H

#include "../activity.h"
#include "../contexts/changebrightnesscontext.h"

#include "illumination/interfaces/IIlluminationManager.h"

namespace Interaction {
namespace Activities {

class ChangeBrightnessActivity : public Activity
{
    Contexts::ChangeBrightnessContext *_context;
    IIlluminationManager *_illuminationsManager;

public:
    explicit ChangeBrightnessActivity(Contexts::ChangeBrightnessContext *context, IIlluminationManager *illuminationsManager, QObject *parent = 0);

    virtual void run ();
    virtual void dispose () { }
};

}
}

#endif // CHANGEBRIGHTNESSACTIVITY_H
