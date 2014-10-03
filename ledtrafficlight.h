#ifndef LEDTRAFFICLIGHT_H
#define LEDTRAFFICLIGHT_H

#include <QObject>
#include <gpio/gpioproducer.h>

class LedTrafficlight : public QObject
{
    Q_OBJECT
public:
    explicit LedTrafficlight(GpioProducer *gpioProducer, QObject *parent = 0);

public slots:
    void lightTrafficlight (int light);

private:
    static constexpr unsigned count = 5;
    Gpio *gpios[count];
};

#endif // LEDTRAFFICLIGHT_H
