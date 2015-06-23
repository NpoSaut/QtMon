#ifndef MODULESACTIVITYVIEWMODEL_H
#define MODULESACTIVITYVIEWMODEL_H

#include <QDeclarativeItem>

#include "qtBlokLib/modulesactivity.h"

namespace ViewModels
{

class ModulesActivityViewModel : public QDeclarativeItem
{
    Q_OBJECT

    // private properties start
    // БС-ДПС
    bool bsDpsActivityValue;
    Q_PROPERTY(bool bsDpsActivity READ getBsDpsActivity WRITE setBsDpsActivity NOTIFY bsDpsActivityChanged)

    // Монитор
    bool monitorActivityValue;
    Q_PROPERTY(bool monitorActivity READ getMonitorActivity WRITE setMonitorActivity NOTIFY monitorActivityChanged)

    // ИПД
    bool ipdActivityValue;
    Q_PROPERTY(bool ipdActivity READ getIpdActivity WRITE setIpdActivity NOTIFY ipdActivityChanged)

    // МП-АЛС
    bool mpAlsActivityValue;
    Q_PROPERTY(bool mpAlsActivity READ getMpAlsActivity WRITE setMpAlsActivity NOTIFY mpAlsActivityChanged)

    // ЭК
    bool electronicMapActivityValue;
    Q_PROPERTY(bool electronicMapActivity READ getElectronicMapActivity WRITE setElectronicMapActivity NOTIFY electronicMapActivityChanged)

    // GPS
    bool gpsActivityValue;
    Q_PROPERTY(bool gpsActivity READ getGpsActivity WRITE setGpsActivity NOTIFY gpsActivityChanged)

    // УКТОЛ (ВДС)
    bool uktolOrVdsActivityValue;
    Q_PROPERTY(bool uktolOrVdsActivity READ getUktolOrVdsActivity WRITE setUktolOrVdsActivity NOTIFY uktolOrVdsActivityChanged)

    // САУТ
    bool sautActivityValue;
    Q_PROPERTY(bool sautActivity READ getSautActivity WRITE setSautActivity NOTIFY sautActivityChanged)

    // РК (Шлюз CAN-MVB2)
    bool radioOrCanMvb2ActivityValue;
    Q_PROPERTY(bool radioOrCanMvb2Activity READ getRadioOrCanMvb2Activity WRITE setRadioOrCanMvb2Activity NOTIFY radioOrCanMvb2ActivityChanged)

    // ЭПК-151Д (Вывод)
    bool epk151dOrOutputActivityValue;
    Q_PROPERTY(bool epk151dOrOutputActivity READ getEpk151dOrOutputActivity WRITE setEpk151dOrOutputActivity NOTIFY epk151dOrOutputActivityChanged)

    // ТСКБМ-К
    bool tskbmActivityValue;
    Q_PROPERTY(bool tskbmActivity READ getTskbmActivity WRITE setTskbmActivity NOTIFY tskbmActivityChanged)

    // МСУЛ
    bool msulActivityValue;
    Q_PROPERTY(bool msulActivity READ getMsulActivity WRITE setMsulActivity NOTIFY msulActivityChanged)

    // private properties end

public:
    explicit ModulesActivityViewModel(QDeclarativeItem *parent = 0);

    // public properties getters start
    bool getBsDpsActivity() const;
    bool getMonitorActivity() const;
    bool getIpdActivity() const;
    bool getMpAlsActivity() const;
    bool getElectronicMapActivity() const;
    bool getGpsActivity() const;
    bool getUktolOrVdsActivity() const;
    bool getSautActivity() const;
    bool getRadioOrCanMvb2Activity() const;
    bool getEpk151dOrOutputActivity() const;
    bool getTskbmActivity() const;
    bool getMsulActivity() const;
    // public properties getters end

signals:
    // properties signals start
    void bsDpsActivityChanged(const bool value);
    void monitorActivityChanged(const bool value);
    void ipdActivityChanged(const bool value);
    void mpAlsActivityChanged(const bool value);
    void electronicMapActivityChanged(const bool value);
    void gpsActivityChanged(const bool value);
    void uktolOrVdsActivityChanged(const bool value);
    void sautActivityChanged(const bool value);
    void radioOrCanMvb2ActivityChanged(const bool value);
    void epk151dOrOutputActivityChanged(const bool value);
    void tskbmActivityChanged(const bool value);
    void msulActivityChanged(const bool value);
    // properties signals end

public slots:
    // public properties setters start
    void setBsDpsActivity(const bool);
    void setMonitorActivity(const bool);
    void setIpdActivity(const bool);
    void setMpAlsActivity(const bool);
    void setElectronicMapActivity(const bool);
    void setGpsActivity(const bool);
    void setUktolOrVdsActivity(const bool);
    void setSautActivity(const bool);
    void setRadioOrCanMvb2Activity(const bool);
    void setEpk151dOrOutputActivity(const bool);
    void setTskbmActivity(const bool);
    void setMsulActivity(const bool);
    // public properties setters end
    
};

}

#endif // MODULESACTIVITYVIEWMODEL_H
