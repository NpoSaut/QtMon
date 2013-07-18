#include "levithan.h"

using namespace sound;

Levithan::Levithan(QObject *parent) :
    QObject(parent),
    speaker()
{
    speaker.start();
}

void Levithan::SayHello(int i)
{
    //TPBTVLWV.WAV
    speaker.EnqueuePhrase(Phrase("phrases/Внимание 1.wav"));
    speaker.EnqueuePhrase(Phrase("play3.wav"));
}

void Levithan::SayLightIndex(int i)
{
    //TPBTVLWV.WAV
    speaker.EnqueuePhrase(Phrase("phrases/Внимание 1.wav", 0));
    switch (i)
    {
        case -1: speaker.EnqueuePhrase(Phrase("phrases/белый.wav")); break;
        case  0: speaker.EnqueuePhrase(Phrase("phrases/красный.wav")); break;
        case  1: speaker.EnqueuePhrase(Phrase("phrases/впереди красный.wav")); break;
        case  2: speaker.EnqueuePhrase(Phrase("phrases/впереди желтый.wav")); break;
        case  3: speaker.EnqueuePhrase(Phrase("phrases/впереди зеленый.wav")); break;
    }
}
