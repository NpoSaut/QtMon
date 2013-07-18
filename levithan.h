#ifndef LEVITHAN_H
#define LEVITHAN_H

#include <QObject>
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

};

#endif // LEVITHAN_H
