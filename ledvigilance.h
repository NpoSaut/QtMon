#ifndef LEDVIGILANCE_H
#define LEDVIGILANCE_H

#include <QObject>
#include <QTimer>
#include "gpio/gpioproducer.h"

class LedVigilance : public QObject
{
    Q_OBJECT
public:
    explicit LedVigilance(GpioProducer *gpioProducer, QObject *parent = 0);

signals:

public slots:
    void doBlinking (bool b);

private slots:
    void timerEvent ();

private:
    QTimer timer;
    int step, active;
    Gpio *red, *yellow;

    void doStep (int s);
};

#endif // LEDVIGILANCE_H
