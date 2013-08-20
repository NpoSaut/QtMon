#ifndef WIN32
#include "unistd.h"
#endif

#include "masqarade.h"
#include "sktcan.h"
#include "cansendqueue.h"

using namespace CanInternals;

CanSendQueue CanInternals::canSendQueue;

void CanSendQueue::push(CanFrame f)
{
    this->enqueue(f);
}

void CanSendQueue::process(CanFrame f)
{
    #ifndef WIN32
    usleep (100);
    writeSocket.send (f);
    usleep (100);
    #endif
}

int CanSendQueue::compare(CanFrame a, CanFrame b)
{
    return b.getId() - a.getId();
}
