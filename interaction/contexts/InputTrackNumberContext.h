#ifndef INPUTTRACKNUMBERCONTEXT_H
#define INPUTTRACKNUMBERCONTEXT_H

#include "cookiescontext.h"

namespace Interaction {
namespace Contexts {

class InputTrackNumberContext : public CookiesContext
{
public:
    InputTrackNumberContext(Cookies *cookies);
    int trackNumber;
    int regularity;
    Record *cookieRecord;
};

}
}

#endif // INPUTTRACKNUMBERCONTEXT_H
