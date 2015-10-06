#include "Max100500TrafficlightView.h"

Max100500TrafficlightView::Max100500TrafficlightView(TrafficLightViewModel *viewModel, Max100500 *max100500)
    : _viewModel(viewModel), _max(max100500)
{
    connect(_viewModel, SIGNAL(numberChanged(int)), this, SLOT(onNumberChanged(int)));
}

void Max100500TrafficlightView::onNumberChanged(int value)
{
    if (value >= 0)
        _max->setNumber(value);
    else
    {
        _max->clear();
    }
}
