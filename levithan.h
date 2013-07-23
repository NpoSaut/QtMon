#ifndef LEVITHAN_H
#define LEVITHAN_H

#include <QObject>
#include <QSound>

#include "sound/speakingthread.h"

class Levithan : public QObject
{
    Q_OBJECT

private:
    sound::SpeakingThread speaker;

public:
    explicit Levithan(QObject *parent = 0);
    
signals:
    
public slots:
    void SayHello(int i);
    void SayLightIndex(int i);

    void Beep();
    void Beep(int i);
    void Beep(bool b);

    void BeepHigh();
};

#endif // LEVITHAN_H
