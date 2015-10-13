#ifndef SPEAKER_H
#define SPEAKER_H

#include "IMouthFactory.h"
#include "phrase.h"
#include "qtDoodahLib/ThreadWithWorker.h"
#include "Speaker/PhrasePriorityQueue.h"

namespace Sound {

class Speaker
{
public:
    Speaker(IMouthFactory *mouthFactory);

    void enqueuePhrase(Phrase phrase);

private:
    SpeakerInternals::PhrasePriorityQueue queue;
    ThreadWithWorker mouthThread;
};

}


#endif // SPEAKER_H
