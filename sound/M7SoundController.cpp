#include "M7SoundController.h"

using namespace Sound;


M7SoundController::M7SoundController(ViewModels::SystemStateViewModel *viewModel, Interaction::Keyboard *keyboard, ILevithan *levithan, QObject *parent)
    : QObject (parent)
{
    QObject::connect(viewModel, SIGNAL(IsEpvReadyChanged(bool)), levithan, SLOT(beepHigh()));
    QObject::connect(keyboard, SIGNAL(keyDown(Interaction::Keyboard::Key)), levithan, SLOT(beepHigh()));

    QObject::connect(viewModel, SIGNAL(SpeedWarningFlash()), levithan, SLOT(beepLong()));
//    QObject::connect(viewModel, SIGNAL(WarningLedFlash()), levithan, SLOT(beepLong()));
}
