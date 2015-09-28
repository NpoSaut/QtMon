#include "Max100500TrafficlightViewModel.h"

Max100500TrafficlightViewModel::Max100500TrafficlightViewModel(TrafficLightViewModel *viewModel, Max100500 *max100500)
    : _viewModel(viewModel), _max(max100500)
{
    connect(_viewModel, SIGNAL(numberChanged(int)), this, SLOT(onNumberChanged(int)));
}

void Max100500TrafficlightViewModel::onNumberChanged(int value)
{
    _max->setNumber(value);
}
