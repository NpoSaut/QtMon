#ifndef SPEAKINGTHREAD_H
#define SPEAKINGTHREAD_H

#include <QThread>
#include <QVector>
#include <QSound>
#include <QMutex>

#include "phrase.h"
#include "queues.h"

namespace sound
{
    class Speaker : public Queues::SimpleQueueBase<Phrase>
    {
    public:
        Speaker();
        void EnqueuePhrase(Phrase phrase);

    protected:
        void process(Phrase phrase);

    };
}

#endif // SPEAKINGTHREAD_H
