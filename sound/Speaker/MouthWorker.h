#ifndef MOUTHWORKER_H
#define MOUTHWORKER_H

#include "qtDoodahLib/IThreadWorker.h"
#include "qtDoodahLib/queues/IThreadSafeQueue.h"
#include "../IMouthFactory.h"
#include "../phrase.h"

namespace Sound {
namespace SpeakerInternals {

class MouthWorker : public IThreadWorker
{
    Q_OBJECT
public:
    explicit MouthWorker(IMouthFactory *mouthFactory, IThreadSafeQueue<Phrase> *queue, QObject *parent = 0);

public slots:
    virtual void run ();

private:
    IMouthFactory *mouthFactory;
    IMouth *mouth;
    IThreadSafeQueue<Phrase> *queue;
};

}
}

#endif // MOUTHWORKER_H
