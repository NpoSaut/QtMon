#include "records/staterecorder.h"

StateRecorder::StateRecorder(QFile &file, const SystemStateViewModel *state, QObject *parent) :
    QObject(parent),
    file (file),
    timer (),
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
    serializer.SerializeTo(state, &stream);
    file.close();
}
