#include "ledvigilance.h"

#include "gpio/gpioproducer.h"

#include <QDebug>

LedVigilance::LedVigilance(GpioProducer *gpioProducer, QObject *parent) :
    QObject(parent),
    timer (),
    step (0),
    active (-1),
    red (gpioProducer->produce(129)),
    yellow (gpioProducer->produce(128))
{
    red->setDirection(Gpio::OUT);
    yellow->setDirection(Gpio::OUT);

    timer.setSingleShot(true);
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(timerEvent()));
}

void LedVigilance::doBlinking(bool b)
{
    if (active != b)
    {
        active = b;
        if (active)
            doStep (0);
    }
}

void LedVigilance::timerEvent()
{
    if (active)
        doStep (step = (step+1) % 4);
    else
        red->setValue(0);
}

void LedVigilance::doStep(int s)
{
    switch (s) {
    case 0:
        red->setValue(1);
        timer.start(50);
        break;
    case 1:
        red->setValue(0);
        timer.start(20);
        break;
    case 2:
        red->setValue(1);
        timer.start(50);
        break;
    case 3:
    default:
        red->setValue(0);
        timer.start(1000);
        break;
    }
}
