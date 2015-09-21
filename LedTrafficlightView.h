#ifndef LEDTRAFFICLIGHTVIEW_H
#define LEDTRAFFICLIGHTVIEW_H

#include "viewmodels/TrafficLightViewModel.h"
#include "gpio/gpioproducer.h"

class LedTrafficlightView : public QObject
{
    Q_OBJECT
public:
    explicit LedTrafficlightView(TrafficLightViewModel *viewModel, GpioProducer *producer, QObject *parent = 0);

private slots:
    void onLightsChanged (int state);

private:
    TrafficLightViewModel *viewModel;
    static constexpr unsigned count = 5;
    Gpio *gpios[count];
};

#endif // LEDTRAFFICLIGHTVIEW_H
