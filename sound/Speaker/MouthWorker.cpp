#include "MouthWorker.h"

using namespace Sound;
using namespace SpeakerInternals;

MouthWorker::MouthWorker(IMouthFactory *mouthFactory, IThreadSafeQueue<Phrase> *queue)
    : IThreadWorker (),
      mouthFactory (mouthFactory),
      mouth (nullptr),
      queue (queue)
{ }

void MouthWorker::run()
{
    if (!mouth)
        mouth = mouthFactory->produce(this);

    forever {
        mouth->say(queue->dequeue().getFile());
    }
}
