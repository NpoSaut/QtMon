#ifndef SPEAKINGTHREAD_H
#define SPEAKINGTHREAD_H

#include <QThread>
#include <QVector>
#include <QSound>
#include <QMutex>

#include "phrase.h"

namespace sound
{
    class SpeakingThread : public QThread
    {
        Q_OBJECT

    private:
        QVector<Phrase>* Speach;
        QMutex speachMutex;

    protected:
        void run();

    public:
        explicit SpeakingThread(QObject *parent = 0);

    signals:

    public slots:
        void EnqueuePhrase(Phrase phrase);

    };
}

#endif // SPEAKINGTHREAD_H
