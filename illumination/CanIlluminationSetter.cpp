#include "CanIlluminationSetter.h"

CanIlluminationSetter::CanIlluminationSetter(IIlluminationManager *manager, Parser *parser, QObject *parent) :
    QObject(parent),
    manager (manager)
{
    QObject::connect(&parser->bilBrightnessLevel, SIGNAL(brightnessRequested(int)), this, SLOT(onIlluminationSet(int)));
}

void CanIlluminationSetter::onIlluminationSet(int value)
{
    manager->setIllumination(double (value)/7);
}
