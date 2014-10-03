#ifndef STATERECORDER_H
#define STATERECORDER_H

#include <QObject>
#include <QFile>
#include <QTimer>
#include "systemstateviewmodel.h"
#include "../stateserializer.h"

class StateRecorder : public QObject
{
    Q_OBJECT
public:
    explicit StateRecorder(QFile &file, const SystemStateViewModel *state,  QObject *parent = 0);

    void start ();
    void stop ();

signals:

private slots:
    void saveFrame ();

private:
    QFile &file;
    QTimer timer;
    const SystemStateViewModel *state;
    StateSerializer serializer;
};

#endif // STATERECORDER_H
