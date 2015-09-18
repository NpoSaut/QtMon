#include "LedTrafficlightView.h"

LedTrafficlightView::LedTrafficlightView(TrafficLightViewModel *viewModel, GpioProducer *producer, QObject *parent) :
    QObject(parent),
    viewModel (viewModel),
    gpios ({producer->produce(125),
            producer->produce(124),
            producer->produce(122),
            producer->produce(121),
            producer->produce(120)})
{
    for (unsigned i = 0; i < count; i ++)
        gpios[i]->setDirection(Gpio::OUTPUT);

    QObject::connect(viewModel, SIGNAL(lightsMaskChanged(int)), this, SLOT(onLightsMaskChanged(int)));
    onLightsMaskChanged(viewModel->lights());
}

void LedTrafficlightView::onLightsMaskChanged(int state)
{
    for (int i = 0; i < count; i ++)
        gpios[i]->setValue(state & (1 << i));
}
