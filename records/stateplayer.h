#ifndef STATEPLAYER_H
#define STATEPLAYER_H

#include <QObject>
#include <QFile>
#include <QTimer>
#include "viewmodels/systemstateviewmodel.h"
#include "../stateserializer.h"

class StatePlayer : public QObject
{
    Q_OBJECT
public:
    explicit StatePlayer(QString fileName, ViewModels::SystemStateViewModel *state,  QObject *parent = 0);
    ~StatePlayer ();

    void start ();
    void stop ();
    void reset ();

signals:

private slots:
    void playFrame ();

private:
    QFile file;
    QTimer timer;
    ViewModels::SystemStateViewModel *state;
    QTextStream stream;
    StateSerializer serializer;
};

#endif // STATEPLAYER_H
