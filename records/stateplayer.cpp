#include "stateplayer.h"

StatePlayer::StatePlayer(QString fileName, SystemStateViewModel *state, QObject *parent) :
    QObject(parent),
    file (fileName),
    timer (),
    state (state),
    stream (&file),
    serializer ()
{
    file.open(QIODevice::ReadOnly);
    stream.setCodec("UTF-8");
    timer.setInterval(500);
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(playFrame()));
}

StatePlayer::~StatePlayer()
{
    file.close();
}

void StatePlayer::start()
{
    timer.start();
}

void StatePlayer::stop()
{
    timer.stop();
}

void StatePlayer::reset()
{
    stream.seek(0);
}

void StatePlayer::playFrame()
{
    if (stream.atEnd()) reset();
    serializer.DeserializeFrom(state, &stream);
}
