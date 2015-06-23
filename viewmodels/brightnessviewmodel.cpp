#include "brightnessviewmodel.h"

ViewModels::BrightnessViewModel::BrightnessViewModel(QObject *parent) :
    QObject(parent)
{
}

void ViewModels::BrightnessViewModel::associateManager(IIlluminationManager *illuminationManager)
{
    _illuminationManager = illuminationManager;
}

int ViewModels::BrightnessViewModel::brightness() const
{
    if (_illuminationManager == nullptr) return 5;
    return _illuminationManager->illumination() * 9;
}

void ViewModels::BrightnessViewModel::setBrightness(int value)
{
    if (_illuminationManager == nullptr) return;
    _illuminationManager->setIllumination(value / 9.0);
}
