#include "MouthWorker.h"

using namespace Sound;
using namespace SpeakerInternals;


MouthWorker::MouthWorker(IMouth *mouth, IThreadSafeQueue<Phrase> *queue, QObject *parent)
    : IThreadWorker (parent),
      mouth (mouth),
      queue (queue)
{ }

void MouthWorker::run()
{
    forever {
        mouth->say(queue->dequeue().file);
    }
}
