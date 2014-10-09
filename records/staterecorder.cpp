#include "records/staterecorder.h"

StateRecorder::StateRecorder(QString fileName, const SystemStateViewModel *state, QObject *parent) :
    QObject(parent),
    file (fileName),
    timer (this),
    state (state),
    serializer()
{
    timer.setInterval(500);
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(saveFrame()));
}

void StateRecorder::start()
{
    timer.start();
}

void StateRecorder::stop()
{
    timer.stop();
}

void StateRecorder::saveFrame()
{
    file.open(QIODevice::Append | QIODevice::WriteOnly);
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    serializer.SerializeTo(state, &stream);
    file.close();
}
