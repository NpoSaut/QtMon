#include "ledtrafficlight.h"

LedTrafficlight::LedTrafficlight(QObject *parent) :
    QObject(parent),
#ifdef Q_OS_LINUX
    producer (GpioProducer::LINUX),
#endif
#ifdef Q_OS_WIN
    producer (GpioProducer::DUMMY),
#endif
    gpios ({producer.produce(125),
            producer.produce(124),
            producer.produce(122),
            producer.produce(121),
           producer.produce(120)})
{
    for (unsigned i = 0; i < count; i ++)
        gpios[i]->setDirection(Gpio::OUT);
}

void LedTrafficlight::lightTrafficlight(int light)
{
    for (int i = 0; i < count; i ++)
        gpios[i]->setValue(i == light);
}
