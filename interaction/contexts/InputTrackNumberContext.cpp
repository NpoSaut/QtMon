#include "InputTrackNumberContext.h"

Interaction::Contexts::InputTrackNumberContext::InputTrackNumberContext(Cookies *cookies) :
    CookiesContext({{&cookies->trackNumbetNotSaved, "ЗАПРЕЩЕНО"}}),
    trackNumber(trackNumber),
    regularity(regularity),
    cookieRecord (&records[0])
{

}
