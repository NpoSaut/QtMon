#include "TrafficLightViewModel.h"

TrafficLightViewModel::TrafficLightViewModel(QObject *parent) :
    QObject(parent),
    _code(-1), _lights(0x0), _mask(0xf), _blink(0), _number(0), _timer(new QTimer(this))
{
    connect(this, SIGNAL(codeChanged(int)), this, SLOT(processCode()));
    connect(_timer, SIGNAL(timeout()), this, SLOT(tick()));
    _timer->start(500);
    processCode();
}

int TrafficLightViewModel::lights()
{
    return _lights & (_mask | (~_blink));
}

void TrafficLightViewModel::processCode()
{
    // Dark Zone
    if (code() < 0)
    {
        _lights = 0;
        _blink = 0;
    }
    // Classic Zone
    else if (code() >= 0 && code() <= 4)
    {
        _lights = 1 << code();
        _blink = 0;
    }
    // ALSN Zone
    else if (code() >= 8 && code() <= 10)
    {
        _lights = 1 << (code() - 8);
        _blink = 0x1;
    }
    else if (code() >= 11)
    {
        _lights = (1 << 3) | (((1 << (code() - 11)) - 1) << 4);
        _blink = 0;
    }
    refresh();

    _number = std::max(0, code() - 11);
    emit numberChanged(number());
}

void TrafficLightViewModel::tick()
{
    _mask = ~_mask;
    if (_blink & _lights != 0)
        refresh();
}

void TrafficLightViewModel::refresh()
{
    emit lightsMaskChanged(lights());
}
