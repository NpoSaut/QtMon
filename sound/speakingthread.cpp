#include "speakingthread.h"

using namespace sound;

SpeakingThread::SpeakingThread(QObject *parent) :
    QThread(parent),
    Speach(), mouth(""), speachMutex()
{
}

void SpeakingThread::EnqueuePhrase(Phrase phrase)
{
    speachMutex.lock();
    Speach.append(phrase);
    speachMutex.unlock();
}


void sound::SpeakingThread::run()
{
    while (true)
    {
        if (Speach.size() > 0)
        {
            speachMutex.lock();
            Phrase phrase = Speach[0];
            Speach.remove(0);
            speachMutex.unlock();

            mouth.play(phrase.fileName);

#ifdef WIN32
            sleep(1);
#else
            while (!mouth.isFinished()) {}
#endif
        }
    }
}
