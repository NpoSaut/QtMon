#include "BaseConfiguration.h"

BaseConfiguration::BaseConfiguration(QObject *parent) :
    IConfiguration(parent),
    breakAssistRequired (false)
{ }

void BaseConfiguration::setBreakAssistRequired(bool v, bool forceSignal)
{
    if ( breakAssistRequired != v || forceSignal )
    {
        breakAssistRequired = v;
        emit breakAssistRequiredChanged (v);
    }
}
