#include "levithan.h"
#include <QDebug>

using namespace sound;

Levithan::Levithan(SystemStateViewModel *state, QObject *parent) :
    QObject(parent),
    state (state),
    speaker()
{
    QObject::connect (state, SIGNAL(IsVigilanceRequiredChanged(bool)), this, SLOT(onStateVigilanceRequiredChanged(bool)));
}

void Levithan::sayHello(int i)
{

}

void Levithan::sayLightIndex(int i)
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

void Levithan::beep()
{
    speaker.enqueuePhrase(Phrase("phrases/beep-700-40.wav", 0));
}

void Levithan::beep(int i) { beep(); }
void Levithan::beep(bool b) { beep(); }

void Levithan::beepHigh()
{
    speaker.enqueuePhrase(Phrase("phrases/beep-900-40.wav", 0));
}

void Levithan::beepVigilance()
{
    speaker.enqueuePhrase(Phrase("phrases/beep-700-160.wav", -1));
}

void Levithan::beepConfirmation()
{
    speaker.enqueuePhrase(Phrase("phrases/beep-low-hi.wav", -1));
}

void Levithan::beepNotification()
{
    speaker.enqueuePhrase (Phrase("phrases/beep-notification.wav", 50));
}

void Levithan::proccessNewVigilanceRequired(bool required)
{
    if (required)
        beepNotification ();
}

void Levithan::proccessNewPreAlarmActive(bool active)
{
    if (active)
        beepNotification ();
}

void Levithan::proccessNewEpvReady(bool ready)
{
    beepHigh ();
}

