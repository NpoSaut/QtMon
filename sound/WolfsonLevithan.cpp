#include "WolfsonLevithan.h"

using namespace Sound;

WolfsonLevithan::WolfsonLevithan(Speaker *speaker, QObject *parent) :
    ILevithan(parent),
    speaker (speaker),
    prevLightIndex (0)
{

}

void WolfsonLevithan::sayLightIndex(Trafficlight l)
{
    int i = (int)l;
    // Говорим "внимание", если сигнал ограничивающий (не "зелёный")
    if ((i >= 0 && i <= 3)
            || (i >= 8 && i <= 11))
        speaker->enqueuePhrase(Phrase("phrases/attention.mp3", 0.3));

    // Проговариваем сигнал
    switch (i)
    {
        case 0:
        case 8:
            speaker->enqueuePhrase(Phrase("phrases/white.mp3")); break;
        case 1:
        case 9:
            speaker->enqueuePhrase(Phrase("phrases/red.mp3")); break;
        case 2:
        case 10:
            speaker->enqueuePhrase(Phrase("phrases/red ahead.mp3")); break;
        case 3:
        case 11:
            speaker->enqueuePhrase(Phrase("phrases/yellow ahead.mp3")); break;
        case 5:
        case 6:
        case 7:
            break;
        default:
            if ( prevLightIndex != 4 && prevLightIndex < 12 )
                speaker->enqueuePhrase(Phrase("phrases/green ahead.mp3"));
            else
                speaker->enqueuePhrase(Phrase("phrases/beep-700-40.mp3"));
            break;
    }
    prevLightIndex = i;
}

void WolfsonLevithan::beep()
{
    speaker->enqueuePhrase(Phrase("phrases/beep-700-40.mp3", 0.3));
}

void WolfsonLevithan::beepHigh()
{
    speaker->enqueuePhrase(Phrase("phrases/beep-900-40.mp3", 0.3));
}

void WolfsonLevithan::beepLong()
{
    speaker->enqueuePhrase(Phrase("phrases/beep-700-160.mp3", 0.1));
}

void WolfsonLevithan::beepLowHi()
{
    speaker->enqueuePhrase(Phrase("phrases/beep-low-hi.mp3", 0.1));
}

void WolfsonLevithan::beepNotification()
{
    speaker->enqueuePhrase (Phrase("phrases/beep-notification.mp3", 0.8));
}


