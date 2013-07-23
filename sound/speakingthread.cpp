#include "speakingthread.h"
#include <QDebug>
#include <QApplication>

using namespace sound;

SpeakingThread::SpeakingThread(QObject *parent) :
    QThread(parent),
    speachMutex()
{
    QSound::play ("phrases/attention.wav");
}

void SpeakingThread::EnqueuePhrase(Phrase phrase)
{
    speachMutex.lock();
    if (Speach != nullptr)
    {
        if (phrase.priority != 0 || Speach->size() == 0)
        {
            qDebug() << "chah " << phrase.fileName;
            int i;
            for (i = 0; i < Speach->size(); i++)
            {
                if (Speach->at(i).priority > phrase.priority) break;
            }
            Speach->insert(i, phrase);
            //Speach->append(phrase);
            qDebug() << "insert at " << i;
        }
    }
    speachMutex.unlock();
}


void sound::SpeakingThread::run()
{
    Speach = new QVector<Phrase>();
    while (true)
    {
        speachMutex.lock();
        int ssize = Speach->size ();
        speachMutex.unlock();

        if (ssize > 0)
        {
            speachMutex.lock();
            Phrase phrase = Speach->at(0);
            Speach->remove(0);
            speachMutex.unlock();

            QSound mouth(phrase.fileName);
            mouth.play();

#ifdef WIN32
            sleep(1);
#else
            while (!mouth.isFinished()) { /*qDebug (".");*/ }
#endif
        }
    }
}
