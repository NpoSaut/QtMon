#ifndef STATERECORDER_H
#define STATERECORDER_H

#include <QObject>
#include <QFile>
#include <QTimer>
#include "viewmodels/systemstateviewmodel.h"
#include "../stateserializer.h"

class StateRecorder : public QObject
{
    Q_OBJECT
public:
    explicit StateRecorder(QString fileName, const ViewModels::SystemStateViewModel *state,  QObject *parent = 0);

    void start ();
    void stop ();

signals:

private slots:
    void saveFrame ();

private:
    QFile file;
    QTimer timer;
    const ViewModels::SystemStateViewModel *state;
    StateSerializer serializer;
};

#endif // STATERECORDER_H
