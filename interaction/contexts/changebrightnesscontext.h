#ifndef CHANGEBRIGHTNESSCONTEXT_H
#define CHANGEBRIGHTNESSCONTEXT_H

#include "../context.h"

namespace Interaction {
namespace Contexts {

class ChangeBrightnessContext : public Context
{
public:
    ChangeBrightnessContext(int brightness) : brightness(brightness) {}
    int brightness;
};

}
}

#endif // CHANGEBRIGHTNESSCONTEXT_H
