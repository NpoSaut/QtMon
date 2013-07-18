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
    speaker.EnqueuePhrase(Phrase("beep.wav"));
    speaker.EnqueuePhrase(Phrase("play3.wav"));
}
