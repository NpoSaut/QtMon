#ifndef VERSIONREQUESTCONTEXT_H
#define VERSIONREQUESTCONTEXT_H

#include <QString>
#include "../context.h"

namespace Interaction {
namespace Contexts {

class VersionRequestContext : public Context
{
public:
    VersionRequestContext() { }
    QString versionString;
};

}
}

#endif // VERSIONREQUESTCONTEXT_H
