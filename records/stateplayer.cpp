#include "stateplayer.h"

StatePlayer::StatePlayer(QFile &file, const SystemStateViewModel *state, QObject *parent) :
    QObject(parent),
    file (file),
    timer (),
    state (state),
    stream (&file),
    serializer ()
{
    file.open(QIODevice::ReadOnly);
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
    serializer.SerializeTo(state, &stream);
}
