#include "levithan.h"
#include <QDebug>

using namespace sound;

Levithan::Levithan(QObject *parent) :
    QObject(parent),
    speaker()
{
}

void Levithan::SayHello(int i)
{
    speaker.enqueuePhrase(Phrase("phrases/Внимание 1.wav"));
    speaker.enqueuePhrase(Phrase("play3.wav"));
}

void Levithan::SayLightIndex(int i)
{
    // Говорим "внимание", если сигнал ограничивающий (не "зелёный")
    if (i < 3) speaker.enqueuePhrase(Phrase("phrases/attention.wav", 0));

    // Проговариваем сигнал
    switch (i)
    {
        case -1: speaker.enqueuePhrase(Phrase("phrases/white.wav")); break;
        case  0: speaker.enqueuePhrase(Phrase("phrases/red.wav")); break;
        case  1: speaker.enqueuePhrase(Phrase("phrases/red ahead.wav")); break;
        case  2: speaker.enqueuePhrase(Phrase("phrases/yellow ahead.wav")); break;
        case  3: speaker.enqueuePhrase(Phrase("phrases/green ahead.wav")); break;
    }
}

void Levithan::Beep()
{
    speaker.enqueuePhrase(Phrase("phrases/beep-700-40.wav", 0));
}

void Levithan::Beep(int i) { Beep(); }
void Levithan::Beep(bool b) { Beep(); }

void Levithan::BeepHigh()
{
    speaker.enqueuePhrase(Phrase("phrases/beep-900-40.wav", 0));
}
