#include "ledtrafficlight.h"

LedTrafficlight::LedTrafficlight(GpioProducer *producer, QObject *parent) :
    QObject(parent),
    gpios ({producer->produce(125),
            producer->produce(124),
            producer->produce(122),
            producer->produce(121),
            producer->produce(120)}),
    on (false), light (0)
{
    for (unsigned i = 0; i < count; i ++)
        gpios[i]->setDirection(Gpio::OUT);
}

void LedTrafficlight::lightTrafficlight(int l)
{
    light = l;
    apply ();
}

void LedTrafficlight::setLightUp(bool turnedOn)
{
    on = turnedOn;
    apply ();

}

void LedTrafficlight::apply()
{
    for (int i = 0; i < count; i ++)
        gpios[i]->setValue(i == light && on);
}
