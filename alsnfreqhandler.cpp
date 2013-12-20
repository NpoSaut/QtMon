#include "alsnfreqhandler.h"

AlsnFreqHandler::AlsnFreqHandler(Can *can, Parser *parser, QObject *parent) :
    QObject(parent),
    can (can),
    parser (parser),
    target (-1),
    convergenceCounter (0),
    init (true)
{
    QObject::connect (&parser->mpState, SIGNAL(frequencyChanged(AlsnFrequency)), this, SLOT(proccessNewActualAlsnFreq(AlsnFrequency)));
    QObject::connect (&parser->mpState, SIGNAL(messageReceived()), this, SLOT(proccessNewMpMessage()));
}

void AlsnFreqHandler::proccessNewTargetAlsnFreq(int freq)
{
    target = freq;
}

void AlsnFreqHandler::proccessNewActualAlsnFreq(AlsnFrequency freq)
{
    if ( init )
    {
        init = false;
        emit targetAlsnFreqChanged (getIntFromFreq (freq));
    }
    emit actualAlsnFreqChanged (getIntFromFreq (freq));
}

void AlsnFreqHandler::proccessNewMpMessage()
{
    if ( getIntFromFreq (parser->mpState.getFrequense ()) != target )
    {
        if ( ++convergenceCounter >= 2 )
        {
            convergenceCounter = 0;
            can->transmitMessage (SysKey(SysKey::FREQ, SysKey::PRESS).encode ());
        }
    }
    else
    {
        convergenceCounter = 0;
    }
}

int AlsnFreqHandler::getIntFromFreq(const AlsnFrequency &freq)
{
    int out = 0;
    switch (freq) {
    case FREQ25:
        out = 25;
        break;
    case FREQ50_A:
    case FREQ50_E:
        out = 50;
        break;
    case FREQ75:
        out = 75;
        break;
    default:
        out = 0;
        break;
    }
    return out;
}
