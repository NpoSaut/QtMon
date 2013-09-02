#ifndef SPEAKINGTHREAD_H
#define SPEAKINGTHREAD_H

#include <QThread>
#include <QVector>
#include <QSound>
#include <QMutex>

#include "phrase.h"
#include "qtDoodahLib/queues.h"

namespace sound
{
    class Speaker : public Queues::PriorityQueueBase<Phrase>
    {
    public:
        Speaker();
        void enqueuePhrase(Phrase phrase);

    protected:
        void process(Phrase phrase);
        int compare(Phrase a, Phrase b);

    };
}

#endif // SPEAKINGTHREAD_H
