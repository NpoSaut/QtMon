#include "PhrasePriorityQueue.h"

using namespace Sound;
using namespace SpeakerInternals;

PhrasePriorityQueue::PhrasePriorityQueue()
    : PriorityThreadSafeQueue (1000)
{ }

int PhrasePriorityQueue::compare(Phrase a, Phrase b)
{
    return b.priority - a.priority;
}
