#ifndef MAX100500TRAFFICLIGHTVIEWMODEL_H
#define MAX100500TRAFFICLIGHTVIEWMODEL_H

#include "spi/Max100500.h"
#include "viewmodels/TrafficLightViewModel.h"

class Max100500TrafficlightViewModel : public QObject
{
    Q_OBJECT
public:
    explicit Max100500TrafficlightViewModel(TrafficLightViewModel *viewModel, Max100500 *max100500);

private slots:
    void onNumberChanged (int value);

private:
    TrafficLightViewModel *_viewModel;
    Max100500 *_max;
};

#endif // MAX100500TRAFFICLIGHTVIEWMODEL_H
