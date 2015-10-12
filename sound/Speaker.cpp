#include "Speaker.h"
#include "Speaker/MouthWorker.h"

using namespace Sound;
using namespace SpeakerInternals;

Speaker::Speaker(IMouthFactory *mouthFactory)
    : queue (),
      mouthThread(new MouthWorker(mouthFactory, &queue, 0))
{
    mouthThread.start();
}

void Speaker::enqueuePhrase(Phrase phrase)
{
    queue.enqueue(phrase);
}
