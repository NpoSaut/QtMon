#include "pressureselector.h"

PressureSelector::PressureSelector(Unit unit, Parser *parser, QObject *parent) :
    QObject(parent),
    parser (parser)
{
    setUnit (unit);

    QObject::connect (&parser->uktolDd1, SIGNAL(tcPressureChanged(Pressure)), this, SLOT(updateTcPressure()));
    QObject::connect (&parser->uktolDd1, SIGNAL(tmPressureChanged(Pressure)), this, SLOT(updateTmPressure()));
    QObject::connect (&parser->uktolDd1, SIGNAL(urPressureChanged(Pressure)), this, SLOT(updateUrPressure()));
    QObject::connect (&parser->uktolDd1, SIGNAL(freshChanged(bool)), this, SLOT(updateTcPressure()));
    QObject::connect (&parser->uktolDd1, SIGNAL(freshChanged(bool)), this, SLOT(updateTmPressure()));
    QObject::connect (&parser->uktolDd1, SIGNAL(freshChanged(bool)), this, SLOT(updateUrPressure()));

    QObject::connect (&parser->mvdDd, SIGNAL(tcPressureChanged(Pressure)), this, SLOT(updateTcPressure()));
    QObject::connect (&parser->mvdDd, SIGNAL(tmPressureChanged(Pressure)), this, SLOT(updateTmPressure()));
    QObject::connect (&parser->mvdDd, SIGNAL(freshChanged(bool)), this, SLOT(updateTcPressure()));
    QObject::connect (&parser->mvdDd, SIGNAL(freshChanged(bool)), this, SLOT(updateTmPressure()));
    QObject::connect (&parser->mvdDd, SIGNAL(freshChanged(bool)), this, SLOT(updateUrPressure()));
}

void PressureSelector::setUnit(PressureSelector::Unit unit)
{
    switch (unit) {
    case ATM:
        print = &Pressure::printAtm;
        break;
    case BAR:
        print = &Pressure::printBar;
        break;
    case MPA:
        print = &Pressure::printMpa;
        break;
    }
}

void PressureSelector::updateTcPressure ()
{
    emit tcPressureChagned ( (
                             takeOne ( parser->uktolDd1.isFresh (), parser->uktolDd1.getTcPressure (),
                                       parser->mvdDd.isFresh (), parser->mvdDd.getTcPressure () )
                             .*print)() );
}

void PressureSelector::updateTmPressure ()
{
    emit tmPressureChanged ( (
                                 takeOne ( parser->uktolDd1.isFresh (), parser->uktolDd1.getTmPressure (),
                                           parser->mvdDd.isFresh (), parser->mvdDd.getTmPressure () )
                                 .*print)() );
}

void PressureSelector::updateUrPressure ()
{
    emit urPressureChanged ( (
                                 takeOne ( parser->uktolDd1.isFresh (), parser->uktolDd1.getUrPressure (),
                                           false, parser->uktolDd1.getUrPressure () )
                                 .*print)() );
}

const Pressure &PressureSelector::takeOne(bool aFresh, const Pressure &a, bool bFresh, const Pressure &b)
{
    static const Pressure lack;
    return takeOne (
                aFresh ? a : lack,
                bFresh ? b : lack
                );
}

const Pressure &PressureSelector::takeOne(const Pressure &a, const Pressure &b)
{
    return a.isValid () ? a : b;
}


