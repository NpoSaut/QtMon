#ifndef MAX100500TRAFFICLIGHTVIEW_H
#define MAX100500TRAFFICLIGHTVIEW_H

#include "spi/Max100500.h"
#include "viewmodels/TrafficLightViewModel.h"

class Max100500TrafficlightView : public QObject
{
    Q_OBJECT
public:
    explicit Max100500TrafficlightView(TrafficLightViewModel *viewModel, Max100500 *max100500);

private slots:
    void onNumberChanged (int value);

private:
    TrafficLightViewModel *_viewModel;
    Max100500 *_max;
};

#endif // MAX100500TRAFFICLIGHTVIEW_H
