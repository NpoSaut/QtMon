#ifndef AUTLOCKHANDLER_H
#define AUTLOCKHANDLER_H

#include <QObject>

#include "qtCanLib/can.h"
#include "qtBlokLib/parser.h"

// Задатчик режми автоблокировки (АБ, ПАБ, ЗАБ)
//  Из интерфейса принимает целеой режим и скорость на белы для ПАБ/ЗАБ
//  При инициализации устанваливает целевой режим в интерфейсе равным фактичесчкому
//  Посылает нужное сообьщение AUX_RESOURCE до тех пор, пока режим не установится равным целевому
class AutolockHandler : public QObject
{
    Q_OBJECT
public:
    explicit AutolockHandler(Can *can, Parser *parser, QObject *parent = 0);

    enum AutolockMode
    {
        AB = 0,
        PAB = 1,
        ZAB = 2
    };
    
signals:
    // Испускается при изменении акутального (фактического) режима
    void actualAutolockModeChanged (int mode);  // mode: 0 - АБ, 1 - ПАБ, 2 - ЗАБ
    // Испускает при инициализации для установки целевого режима равным фактическому
    void targetAutlockModeChanged (int mode);// mode: 0 - АБ, 1 - ПАБ, 2 - ЗАБ
    
public slots:
    // Устанавилвает целевой режим АБ
    void setTargetMode (int mode); // mode: 0 - АБ, 1 - ПАБ, 2 - ЗАБ
    // Устанавливает скорость на белый для ПАБ/ЗАБ
    void setWhiteSpeed (int speed);

protected slots:
    // Вызывается с каждым приходом сообщения MP_STATE
    void proccessMpMessage ();
    // Вызывается, когда изменяется состояние автоблокировки
    void proccessAutolockStateChange ();
    
protected:
    AutolockMode getMpAutolockState () const;

    Can *can;
    Parser *parser;

    AutolockMode target;
    int speed;
    bool init;
};

#endif // AUTLOCKHANDLER_H
