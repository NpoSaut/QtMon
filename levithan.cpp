#include "levithan.h"
#include <QDebug>

using namespace sound;

Levithan::Levithan(QObject *parent) :
    QObject(parent),
    speaker()
{
    speaker.start ();
}

void Levithan::SayHello(int i)
{
    speaker.EnqueuePhrase(Phrase("phrases/Внимание 1.wav"));
    speaker.EnqueuePhrase(Phrase("play3.wav"));
}

void Levithan::SayLightIndex(int i)
{
    speaker.EnqueuePhrase(Phrase("phrases/attention.wav", 0));
    switch (i)
    {
        case -1: speaker.EnqueuePhrase(Phrase("phrases/white.wav")); break;
        case  0: speaker.EnqueuePhrase(Phrase("phrases/red.wav")); break;
        case  1: speaker.EnqueuePhrase(Phrase("phrases/red ahead.wav")); break;
        case  2: speaker.EnqueuePhrase(Phrase("phrases/yellow ahead.wav")); break;
        case  3: speaker.EnqueuePhrase(Phrase("phrases/green ahead.wav")); break;
    }
}

