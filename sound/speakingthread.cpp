#include <QDebug>
#include <QApplication>

#include "cDoodahLib/masqarade.h"
#include "speakingthread.h"

using namespace sound;

Speaker::Speaker()
    : PriorityQueueBase()
{
    QSound::play ("phrases/silence.wav");
}

void Speaker::enqueuePhrase(Phrase phrase)
{
    if (phrase.priority == -1 && !this->isEmpty ()) return;

    this->enqueue(phrase);
}


void Speaker::process(Phrase phrase)
{
    QSound mouth(phrase.fileName);
//    qDebug() << "    playing" << phrase.fileName;
    mouth.play();

#ifdef WIN32
    //msleep(40);
#else
    while (!mouth.isFinished()) { /*qDebug (".");*/ }
#endif
}

int Speaker::compare(Phrase a, Phrase b)
{
    return b.priority - a.priority;
}
