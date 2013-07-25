#include <QDebug>
#include <QApplication>

#include "speakingthread.h"

using namespace sound;

Speaker::Speaker()
    : SimpleQueueBase()
{
    QSound::play ("phrases/attention.wav");
}

void Speaker::EnqueuePhrase(Phrase phrase)
{
    enqueue(phrase);
}


void Speaker::process(Phrase phrase)
{
    QSound mouth(phrase.fileName);
    mouth.play();

#ifdef WIN32
    //msleep(40);
#else
    while (!mouth.isFinished()) { /*qDebug (".");*/ }
#endif
}
