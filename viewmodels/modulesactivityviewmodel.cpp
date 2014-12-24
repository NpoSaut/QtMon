#include "modulesactivityviewmodel.h"

namespace ViewModels
{

ModulesActivityViewModel::ModulesActivityViewModel(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    // fileds init start
    bsDpsActivityValue = false;
    monitorActivityValue = false;
    ipdActivityValue = false;
    mpAlsActivityValue = false;
    electronicMapActivityValue = false;
    gpsActivityValue = false;
    uktolOrVdsActivityValue = false;
    sautActivityValue = false;
    radioOrCanMvb2ActivityValue = false;
    epk151dOrOutputActivityValue = false;
    tskbmActivityValue = false;
    msulActivityValue = false;
    // fileds init end
}

// -- start: Properties Getters and Setters --
// БС-ДПС
bool ModulesActivityViewModel::getBsDpsActivity() const
{
    return bsDpsActivityValue;
}
void ModulesActivityViewModel::setBsDpsActivity(const bool value)
{
    if (bsDpsActivityValue != value)
    {
        bsDpsActivityValue = value;
        emit bsDpsActivityChanged(value);
    }
}

// Монитор
bool ModulesActivityViewModel::getMonitorActivity() const
{
    return monitorActivityValue;
}
void ModulesActivityViewModel::setMonitorActivity(const bool value)
{
    if (monitorActivityValue != value)
    {
        monitorActivityValue = value;
        emit monitorActivityChanged(value);
    }
}

// ИПД
bool ModulesActivityViewModel::getIpdActivity() const
{
    return ipdActivityValue;
}
void ModulesActivityViewModel::setIpdActivity(const bool value)
{
    if (ipdActivityValue != value)
    {
        ipdActivityValue = value;
        emit ipdActivityChanged(value);
    }
}

// МП-АЛС
bool ModulesActivityViewModel::getMpAlsActivity() const
{
    return mpAlsActivityValue;
}
void ModulesActivityViewModel::setMpAlsActivity(const bool value)
{
    if (mpAlsActivityValue != value)
    {
        mpAlsActivityValue = value;
        emit mpAlsActivityChanged(value);
    }
}

// ЭК
bool ModulesActivityViewModel::getElectronicMapActivity() const
{
    return electronicMapActivityValue;
}
void ModulesActivityViewModel::setElectronicMapActivity(const bool value)
{
    if (electronicMapActivityValue != value)
    {
        electronicMapActivityValue = value;
        emit electronicMapActivityChanged(value);
    }
}

// GPS
bool ModulesActivityViewModel::getGpsActivity() const
{
    return gpsActivityValue;
}
void ModulesActivityViewModel::setGpsActivity(const bool value)
{
    if (gpsActivityValue != value)
    {
        gpsActivityValue = value;
        emit gpsActivityChanged(value);
    }
}

// УКТОЛ (ВДС)
bool ModulesActivityViewModel::getUktolOrVdsActivity() const
{
    return uktolOrVdsActivityValue;
}
void ModulesActivityViewModel::setUktolOrVdsActivity(const bool value)
{
    if (uktolOrVdsActivityValue != value)
    {
        uktolOrVdsActivityValue = value;
        emit uktolOrVdsActivityChanged(value);
    }
}

// САУТ
bool ModulesActivityViewModel::getSautActivity() const
{
    return sautActivityValue;
}
void ModulesActivityViewModel::setSautActivity(const bool value)
{
    if (sautActivityValue != value)
    {
        sautActivityValue = value;
        emit sautActivityChanged(value);
    }
}

// РК (Шлюз CAN-MVB2)
bool ModulesActivityViewModel::getRadioOrCanMvb2Activity() const
{
    return radioOrCanMvb2ActivityValue;
}
void ModulesActivityViewModel::setRadioOrCanMvb2Activity(const bool value)
{
    if (radioOrCanMvb2ActivityValue != value)
    {
        radioOrCanMvb2ActivityValue = value;
        emit radioOrCanMvb2ActivityChanged(value);
    }
}

// ЭПК-151Д (Вывод)
bool ModulesActivityViewModel::getEpk151dOrOutputActivity() const
{
    return epk151dOrOutputActivityValue;
}
void ModulesActivityViewModel::setEpk151dOrOutputActivity(const bool value)
{
    if (epk151dOrOutputActivityValue != value)
    {
        epk151dOrOutputActivityValue = value;
        emit epk151dOrOutputActivityChanged(value);
    }
}

// ТСКБМ-К
bool ModulesActivityViewModel::getTskbmActivity() const
{
    return tskbmActivityValue;
}
void ModulesActivityViewModel::setTskbmActivity(const bool value)
{
    if (tskbmActivityValue != value)
    {
        tskbmActivityValue = value;
        emit tskbmActivityChanged(value);
    }
}

// МСУЛ
bool ModulesActivityViewModel::getMsulActivity() const
{
    return msulActivityValue;
}
void ModulesActivityViewModel::setMsulActivity(const bool value)
{
    if (msulActivityValue != value)
    {
        msulActivityValue = value;
        emit msulActivityChanged(value);
    }
}

// -- end: Properties Getters and Setters --

}




