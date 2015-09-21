#include "WolfsonLevithan.h"
#include <QDebug>

using namespace sound;

WolfsonLevithan::WolfsonLevithan(QObject *parent) :
    Levithan(parent),
    speaker(),
    prevLightIndex (0)
{

}

void WolfsonLevithan::sayHello(int i)
{

}

void WolfsonLevithan::sayLightIndex(Trafficlight l)
{
    int i = (int)l;
    // Говорим "внимание", если сигнал ограничивающий (не "зелёный")
    if ((i >= 0 && i <= 3)
            || (i >= 8 && i <= 11))
        speaker.enqueuePhrase(Phrase("phrases/attention.wav", 0));

    // Проговариваем сигнал
    switch (i)
    {
        case 0:
        case 8:
            speaker.enqueuePhrase(Phrase("phrases/white.wav")); break;
        case 1:
        case 9:
            speaker.enqueuePhrase(Phrase("phrases/red.wav")); break;
        case 2:
        case 10:
            speaker.enqueuePhrase(Phrase("phrases/red ahead.wav")); break;
        case 3:
        case 11:
            speaker.enqueuePhrase(Phrase("phrases/yellow ahead.wav")); break;
        case 5:
        case 6:
        case 7:
            break;
        default:
            if ( prevLightIndex != 4 && prevLightIndex < 12 )
                speaker.enqueuePhrase(Phrase("phrases/green ahead.wav"));
            else
                speaker.enqueuePhrase(Phrase("phrases/beep-700-40.wav"));
            break;
    }
    prevLightIndex = i;
}

void WolfsonLevithan::beep()
{
    speaker.enqueuePhrase(Phrase("phrases/beep-700-40.wav", 0));
}

void WolfsonLevithan::beep(int i) { beep(); }
void WolfsonLevithan::beep(bool b) { beep(); }

void WolfsonLevithan::beepHigh()
{
    speaker.enqueuePhrase(Phrase("phrases/beep-900-40.wav", 0));
}

void WolfsonLevithan::beepVigilance()
{
    speaker.enqueuePhrase(Phrase("phrases/beep-700-160.wav", -1));
}

void WolfsonLevithan::beepConfirmation()
{
    speaker.enqueuePhrase(Phrase("phrases/beep-low-hi.wav", -1));
}

void WolfsonLevithan::beepNotification()
{
    speaker.enqueuePhrase (Phrase("phrases/beep-notification.wav", 50));
}

void WolfsonLevithan::proccessNewVigilanceRequired(bool required)
{
    if (required)
        beepNotification ();
}

void WolfsonLevithan::proccessNewPreAlarmActive(bool active)
{
    if (active)
        beepNotification ();
}

void WolfsonLevithan::proccessNewEpvReady(bool ready)
{
    beepHigh ();
}

void WolfsonLevithan::proccessVigilanceRequired(bool value)
{
    if (!value)
        beepConfirmation ();
}
