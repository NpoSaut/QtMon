#include "KxSoundController.h"

using namespace Sound;

KxSoundController::KxSoundController(ViewModels::SystemStateViewModel *viewModel, Interaction::Keyboard *keyboard, ILevithan *levithan, QObject *parent)
    : QObject (parent),
      levithan (levithan)
{
    QObject::connect(viewModel->trafficLights(), SIGNAL(codeChanged(Trafficlight)), levithan, SLOT(sayLightIndex(Trafficlight)));

    QObject::connect(viewModel, SIGNAL(ConfirmButtonPressed()), levithan, SLOT(beep()));

    QObject::connect(viewModel, SIGNAL(ButtonPressed()), levithan, SLOT(beepHigh()));
    QObject::connect(viewModel, SIGNAL(IsEpvReadyChanged(bool)), levithan, SLOT(beepHigh()));
    QObject::connect(keyboard, SIGNAL(keyDown(Interaction::Keyboard::Key)), levithan, SLOT(beepHigh()));

    QObject::connect(viewModel, SIGNAL(SpeedWarningFlash()), levithan, SLOT(beepLong()));
    QObject::connect(viewModel, SIGNAL(WarningLedFlash()), levithan, SLOT(beepLong()));
    QObject::connect(viewModel, SIGNAL(TsvcIsVigilanceRequiredChanged(bool)), this, SLOT(proccessTsvcVigilanceRequired(bool)));
    QObject::connect(viewModel, SIGNAL(TsvcIsPreAlarmActiveChanged(bool)), this, SLOT(proccessTsvcPreAlarmActive(bool)));
    QObject::connect(viewModel, SIGNAL(IsVigilanceRequiredChanged(bool)), this, SLOT(proccessVigilanceRequired(bool)));
}

void KxSoundController::proccessTsvcVigilanceRequired(bool required)
{
    if (required)
        levithan->beepNotification ();
}

void KxSoundController::proccessTsvcPreAlarmActive(bool active)
{
    if (active)
        levithan->beepNotification ();
}

void KxSoundController::proccessVigilanceRequired(bool value)
{
    if (!value)
        levithan->beepNotification();
}
