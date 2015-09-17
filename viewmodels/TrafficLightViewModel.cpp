#include <QDebug>

#include "TrafficLightViewModel.h"

TrafficLightViewModel::TrafficLightViewModel(QObject *parent) :
    QObject(parent)
{
    connect(this, SIGNAL(codeChanged(int)), this, SLOT(process()));
}

void TrafficLightViewModel::process()
{
    qDebug() << "light code: " << code();
    // Dark Zone
    if (code() < 0)
    {
        setLightsMask(0);
    }
    // Classic Zone
    else if (code() <= 4)
    {
        setLightsMask(1 << code());
    }
    // ALSN Zone
    else
    {
        setLightsMask(0xff);
    }
}
