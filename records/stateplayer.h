#ifndef STATEPLAYER_H
#define STATEPLAYER_H

#include <QObject>
#include <QFile>
#include <QTimer>
#include "systemstateviewmodel.h"
#include "../stateserializer.h"

class StatePlayer : public QObject
{
    Q_OBJECT
public:
    explicit StatePlayer(QFile &file, const SystemStateViewModel *state,  QObject *parent = 0);
    ~StatePlayer ();

    void start ();
    void stop ();
    void reset ();

signals:

private slots:
    void playFrame ();

private:
    QFile &file;
    QTimer timer;
    const SystemStateViewModel *state;
    QTextStream stream;
    StateSerializer serializer;
};

#endif // STATEPLAYER_H
