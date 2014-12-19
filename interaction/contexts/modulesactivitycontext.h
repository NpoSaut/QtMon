#ifndef MODULESACTIVITYCONTEXT_H
#define MODULESACTIVITYCONTEXT_H

#include <QString>
#include "../context.h"

namespace Interaction {
namespace Contexts {

class ModulesActivityContext : public Context
{
public:
    ModulesActivityContext() { }
    QString activityString;
};

}
}

#endif // MODULESACTIVITYCONTEXT_H
