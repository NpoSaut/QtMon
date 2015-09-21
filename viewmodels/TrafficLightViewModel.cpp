#include "TrafficLightViewModel.h"

TrafficLightViewModel::TrafficLightViewModel(QObject *parent) :
    QObject(parent),
    _code(LIGHT_UNKNOWN), _lights(0x0), _mask(0xf), _blink(0), _number(0), _timer(new QTimer(this)), _enabled(true)
{
    connect(this, SIGNAL(codeChanged(Trafficlight)), this, SLOT(processCode()));
    connect(this, SIGNAL(enabledChanged(bool)), this, SLOT(processEnabled()));
    connect(_timer, SIGNAL(timeout()), this, SLOT(tick()));
    _timer->start(500);
    processCode();
}

int TrafficLightViewModel::lights()
{
    return enabled()
            ? _lights & (_mask | (~_blink))
            : 0x00;
}

void TrafficLightViewModel::processCode()
{
    // Dark Zone
    if (intCode() < 0)
    {
        _lights = 0;
        _blink = 0;
    }
    // Classic Zone
    else if (intCode() >= 0 && intCode() <= 4)
    {
        _lights = 1 << intCode();
        _blink = 0;
    }
    // ALSN Zone
    else if (intCode() >= 8 && intCode() <= 10)
    {
        _lights = 1 << (intCode() - 8);
        _blink = 0x1;
    }
    else if (intCode() >= 11)
    {
        _lights = (1 << 3) | (((1 << (intCode() - 11)) - 1) << 4);
        _blink = 0;
    }
    refresh();

    _number = std::max(0, intCode() - 11);
    emit numberChanged(number());
}

void TrafficLightViewModel::processEnabled()
{
    refresh();
}

void TrafficLightViewModel::tick()
{
    _mask = ~_mask;
    if (_blink & _lights)
        refresh();
}

void TrafficLightViewModel::refresh()
{
    emit lightsChanged(lights());
}
