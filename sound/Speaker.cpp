#include "Speaker.h"
#include "Speaker/MouthWorker.h"

using namespace Sound;
using namespace SpeakerInternals;

Speaker::Speaker(IMouth *mouth)
    : queue (),
      mouthThread(new MouthWorker(mouth, &queue, 0))
{
    mouthThread.start();
}

void Speaker::enqueuePhrase(Phrase phrase)
{
    queue.enqueue(phrase);
}
