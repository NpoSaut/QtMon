#include "TextNotificationModel.h"
#include "qtBlokLib/parsers/drivemode.h"
#include "qmetatype.h"

using namespace ViewModels;

TextNotificationModel::TextNotificationModel(SystemStateViewModel *stateViewModel, QObject *parent) :
    QObject(parent),
    _stateViewModel (stateViewModel),
    _handbrakeHintTimeout (this),
    _handbrakeHintRequired (false),
    _handbrakeHint (false)
{
    _handbrakeHintTimeout.setSingleShot (true);
    _handbrakeHintTimeout.setInterval (15000);
    QObject::connect(&_handbrakeHintTimeout, SIGNAL(timeout()), this, SLOT(setHandbrakeHint()));

    QObject::connect(_stateViewModel, SIGNAL(IsEpvReadyChanged(bool)), this, SLOT(show()));
    QObject::connect(_stateViewModel, SIGNAL(IsEpvReleasedChanged(bool)), this, SLOT(show()));
    QObject::connect(_stateViewModel, SIGNAL(IsSlippingChanged(bool)), this, SLOT(show()));
    QObject::connect(_stateViewModel, SIGNAL(driveModeFactChanged(int)), this, SLOT(show()));
    QObject::connect(_stateViewModel, SIGNAL(IsTractionOnChanged(bool)), this, SLOT(show()));
    QObject::connect(_stateViewModel, SIGNAL(IsInMotionChanged(bool)), this, SLOT(show()));
}

QString TextNotificationModel::getText() const
{
    return _text;
}

bool TextNotificationModel::isHandbrakeHintRequired() const
{
    return _handbrakeHintRequired;
}

void TextNotificationModel::setText(QString arg)
{
    if (_text != arg) {
        _text = arg;
        emit textChanged(arg);
    }
}

void TextNotificationModel::setHandbrakeHintRequired(bool arg)
{
    if (_handbrakeHintRequired != arg) {
        _handbrakeHintRequired = arg;
        emit handbrakeHintRequiredChanged(arg);
    }
}

void TextNotificationModel::show()
{
    if (_handbrakeHintRequired)
    {
        // Подними ручник
        if ( _stateViewModel->getDriveModeFact() != ROAD
         && !_stateViewModel->getIsInMotion()
         &&  _stateViewModel->getIsTractionOn()  )
        {
            if ( !_handbrakeHintTimeout.isActive () )
                _handbrakeHintTimeout.start ();
        }
        else
        {
            _handbrakeHintTimeout.stop ();
            _handbrakeHint = false;
        }
    }

    if ( !_stateViewModel->getIsEpvReady() )
        setText ("Система отключена");

    else if ( _stateViewModel->getIsEpvReleased() )
        setText ("Экстренное торможение");

    else if ( _stateViewModel->getIsSlipping() )
        setText ("Боксование");

    else if ( _handbrakeHint )
        setText ("Подними ручник");

    else
        setText ("");
}

void TextNotificationModel::setHandbrakeHint()
{
    _handbrakeHint = true;
    show ();
}
