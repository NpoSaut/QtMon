#ifndef EXECUTECOMMANDCONTEXT_H
#define EXECUTECOMMANDCONTEXT_H

#include "../context.h"

namespace Interaction {
namespace Contexts {

class ExecuteCommandContext : public Context
{
public:
    ExecuteCommandContext();
    int commandNumber;
};

}
}

#endif // EXECUTECOMMANDCONTEXT_H
