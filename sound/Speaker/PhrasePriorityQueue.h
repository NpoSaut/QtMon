#ifndef PHRASEPRIORITYQUEUE_H
#define PHRASEPRIORITYQUEUE_H

#include "qtDoodahLib/queues/PriorityThreadSafeQueue.h"
#include "../phrase.h"

namespace Sound {
namespace SpeakerInternals {

class PhrasePriorityQueue : public PriorityThreadSafeQueue<Phrase>
{
public:
    PhrasePriorityQueue();

private:
    int compare(Phrase a, Phrase b);
};

}
}


#endif // PHRASEPRIORITYQUEUE_H
